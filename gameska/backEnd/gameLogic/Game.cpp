//
// Created by Metoděj Janota on 24.11.2025.
//

#include "Game.h"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>
#include "./../types/Vec2.h"
#include "../render/RenderEngine.h"
#include "../../frontEnd/Classes/Menu/PauseMenu.h"
#include "../../frontEnd/Classes/Enemy.h"

Game::Game(int screenW, int screenH)
    : m_renderEngine(screenW, screenH)
    , m_inputHandler()
    , m_player(Vec2(0, 0))
    , m_levelLogic(nullptr)
    , m_currentEnemy(nullptr)
    , m_running(false) {
    m_levelLogic = new LevelLogic();
}

Game::~Game() {
    delete m_levelLogic;
    delete m_currentEnemy;
}

void Game::run() {
    m_running = true;
    m_totalTime = 0.0; // Resetování času na začátku každé hry

    // SPUŠTĚNÍ HERNÍ HUDBY
    #ifdef _WIN32
    PlaySound(TEXT("music/dungeon_theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    #endif

    // Inicializace prvního levelu
    m_levelLogic->nextLevel();

    // Příprava pro měření času (startovní bod)
    auto lastTick = std::chrono::steady_clock::now();

    // Nastavení počáteční pozice hráče a kamery na mapě
    Map* currentMap = m_levelLogic->getCurrentMap();
    if (currentMap != nullptr) {
        m_player.setPosition(currentMap->getSpawnPoint());

        // Spawn enemy v první místnosti
        spawnEnemyInCurrentRoom();
    }
    m_renderEngine.getCamera().setPosition(m_player.getPosition());

    // Prvotní vykreslení scény
    m_renderEngine.render(m_player, m_renderEngine.getCamera(),
                         m_levelLogic->getCurrentLevel(), (int)m_totalTime,
                         m_levelLogic->getCurrentMap());

    // HLAVNÍ HERNÍ SMYČKA
    while (m_running) {
        // 1. AKTUALIZACE ČASU
        // Tento blok počítá, kolik času uběhlo od posledního průchodu smyčkou
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - lastTick;
        m_totalTime += elapsed.count();
        lastTick = now;

        // 2. KONTROLA VSTUPU (pokud hráč nic nemačká)
        if (!m_inputHandler.kbhit()) {
            // Překreslujeme UI, aby vteřiny na hodinách běžely plynule
            m_renderEngine.render(m_player, m_renderEngine.getCamera(),
                                 m_levelLogic->getCurrentLevel(), (int)m_totalTime,
                                 m_levelLogic->getCurrentMap());

            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue; // Skočí zpět na začátek while
        }

        // 3. ZÍSKÁNÍ A ZPRACOVÁNÍ PŘÍKAZU
        Command cmd = m_inputHandler.getInput();

        // Filtrování systémových příkazů (NONE, QUIT, PAUSE)
        if (cmd == Command::NONE) continue;

        if (cmd == Command::QUIT) {
            m_running = false;
            continue;
        }

        if (cmd == Command::PAUSE) {
            auto action = PauseMenu::show();
            if (action == PauseMenu::EXIT_TO_MENU) {
                m_running = false;
                continue;
            }
            // Po návratu z menu resetujeme lastTick na aktuální čas,
            // aby se doba strávená v pauze nepřičetla k hernímu času
            lastTick = std::chrono::steady_clock::now();
        }

        // 4. LOGIKA POHYBU
        update(cmd);

        // 5. FINÁLNÍ RENDER (vykreslení po pohybu hráče)
        // 5 parametrů ve správném pořadí: Player, Camera, Level, Time, Map
        m_renderEngine.render(m_player, m_renderEngine.getCamera(),
                             m_levelLogic->getCurrentLevel(), (int)m_totalTime,
                             m_levelLogic->getCurrentMap());
    }

    // Výpisy po ukončení smyčky
    std::cout << "x: " << m_player.getPosition().x << ", y:" << m_player.getPosition().y << std::endl;
    std::cout << "Reached Level: " << m_levelLogic->getCurrentLevel() << std::endl;

    // ZASTAVENÍ HUDBY PŘI KONCI HRY
    #ifdef _WIN32
    PlaySound(NULL, 0, 0);
    #endif
}

void Game::update(Command cmd) {
    Vec2 oldPos = m_player.getPosition();

    // Vypočet nové pozice bez fyzického pohybu
    Vec2 newPos = oldPos;
    switch (cmd) {
        case Command::MOVE_UP:
            newPos.y++;
            break;
        case Command::MOVE_DOWN:
            newPos.y--;
            break;
        case Command::MOVE_LEFT:
            newPos.x--;
            break;
        case Command::MOVE_RIGHT:
            newPos.x++;
            break;
        default:
            return;
    }

    Map* currentMap = m_levelLogic->getCurrentMap();
    if (currentMap != nullptr) {
        // Kontrola, zda je cílová pozice platná
        if (!currentMap->isWalkable(newPos)) {
            return;
        }

        // KONTROLA KOLIZE S ENEMY - Nelze projít přes živého nepřítele
        if (m_currentEnemy && m_currentEnemy->isAlive() &&
            newPos.x == m_currentEnemy->getPosition().x &&
            newPos.y == m_currentEnemy->getPosition().y) {

            std::cout << "\nNarazil jsi na " << m_currentEnemy->getName() << "! Automatický útok!" << std::endl;

            // Pokud se hráč snaží jít na pozici enemy, zaútočí místo toho
            int damage = m_player.attack();
            m_player.resetAttack();

            if (damage > 0) {
                m_currentEnemy->takeDamage(damage);
                std::cout << ">>> Způsobil jsi " << damage << " damage! " << m_currentEnemy->getName() << " HP: " << m_currentEnemy->getHealth() << std::endl;

                if (m_currentEnemy->getHealth() <= 0) {
                    std::cout << "\n*** " << m_currentEnemy->getName() << " BYL PORAŽEN! ***\n" << std::endl;
                    return;  // Enemy je mrtvý, zmizí při dalším renderu
                }
            }

            // Enemy útočí zpět (pouze pokud je naživu)
            if (m_currentEnemy->isAlive()) {
                int enemyDamage = m_currentEnemy->attack();
                if (enemyDamage > 0) {
                    m_player.takeDamage(enemyDamage);
                    std::cout << "<<< " << m_currentEnemy->getName() << " útočí! Dostal jsi " << enemyDamage << " damage! Tvoje HP: " << m_player.getHealth() << "/" << m_player.getMaxHealth() << "\n" << std::endl;

                    // Kontrola smrti hráče
                    if (m_player.getHealth() <= 0) {
                        std::cout << "\n=== GAME OVER ===" << std::endl;
                        std::cout << "Byl jsi poražen!" << std::endl;
                        m_running = false;
                    }
                }
            }
            return;  // Zablokovat pohyb
        }

        // NOVÁ KONTROLA: Vchod (návrat zpět)
        if (currentMap->isRoomEntry(newPos) && m_levelLogic->canGoBack()) {
            m_levelLogic->previousRoom();
            currentMap = m_levelLogic->getCurrentMap();
            if (currentMap != nullptr) {
                // Spawn u východu předchozí místnosti
                Vec2 entrySpawn = getSpawnAtExit(currentMap->getCurrentExit());
                m_player.setPosition(entrySpawn);
                m_renderEngine.getCamera().setPosition(m_player.getPosition());
            }
            return;
        }

        // Kontrola východu (dopředu)
        if (currentMap->isRoomExit(newPos)) {
            m_levelLogic->nextRoom();
            currentMap = m_levelLogic->getCurrentMap();
            if (currentMap != nullptr) {
                // Spawn u vchodu nové místnosti
                Vec2 entrySpawn = getSpawnAtEntry(currentMap->getCurrentEntry());
                m_player.setPosition(entrySpawn);
                m_renderEngine.getCamera().setPosition(m_player.getPosition());

                // Spawn enemy v nové místnosti
                spawnEnemyInCurrentRoom();
            }
            return;
        }

        // Kontrola trapdooru (O) před pohybem - UPROSTŘED SPAWNU
        if (currentMap->isExitTile(newPos)) {
            m_levelLogic->nextLevel();
            currentMap = m_levelLogic->getCurrentMap();
            if (currentMap != nullptr) {
                // Trapdoor = spawn uprostřed
                m_player.setPosition(currentMap->getSpawnPoint());
                m_renderEngine.getCamera().setPosition(m_player.getPosition());

                // Spawn noveho nepritele v nove arene
                spawnEnemyInCurrentRoom();
            }
            return;
        }
    }

    // Pokud vše prošlo, teprve se hráč pohne
    m_player.setPosition(newPos);
    m_renderEngine.getCamera().setPosition(m_player.getPosition());
}

void Game::spawnEnemyInCurrentRoom() {
    Map* currentMap = m_levelLogic->getCurrentMap();
    if (currentMap == nullptr) return;

    // Smazat starého enemy
    delete m_currentEnemy;

    // Vytvořit nového enemy
    Vec2 enemyPos = currentMap->getSpawnPoint();
    enemyPos.x -= 4;  // Vlevo od spawn pointu
    enemyPos.y += 0;  // Stejná výška

    // Název enemy podle levelu
    std::string enemyName = "Goblin";
    int level = m_levelLogic->getCurrentLevel();
    if (level >= 5) enemyName = "Orc";
    if (level >= 10) enemyName = "Troll";

    int enemyHealth = 50 + (level - 1) * 10;  // Víc HP na vyšších levelech

    m_currentEnemy = new Enemy(enemyName, 10, true, enemyHealth, level);
    m_currentEnemy->setPosition(enemyPos);
    currentMap->addObject(m_currentEnemy);

    // Reset časovače pro nového enemy
    m_enemyAttackTimer = 0.0f;

    std::cout << "\n*** OBJEVIL SE " << enemyName << "! ***" << std::endl;
    std::cout << "Level: " << level << " | HP: " << enemyHealth << std::endl;
    std::cout << "Útok mezerníkem! Enemy útočí každých 5 sekund!\n" << std::endl;
}

void Game::updateEnemyAI(float deltaTime) {
    // Pokud není enemy nebo je mrtvý, nic nedělej
    if (!m_currentEnemy || !m_currentEnemy->isAlive()) {
        m_enemyAttackTimer = 0.0f;
        return;
    }

    // Přičti čas
    m_enemyAttackTimer += deltaTime;

    // Pokud uplynulo 5 sekund, enemy zaútočí
    if (m_enemyAttackTimer >= m_enemyAttackInterval) {
        m_enemyAttackTimer = 0.0f;  // Reset časovače

        // Kontrola vzdálenosti k hráči
        Vec2 playerPos = m_player.getPosition();
        Vec2 enemyPos = m_currentEnemy->getPosition();
        int distance = abs(playerPos.x - enemyPos.x) + abs(playerPos.y - enemyPos.y);

        // Enemy útočí pouze pokud je hráč dostatečně blízko (max 5 políček)
        if (distance <= 5) {
            int damage = m_currentEnemy->attack();
            if (damage > 0) {
                m_player.takeDamage(damage);
                std::cout << "\n!!! " << m_currentEnemy->getName() << " ÚTOČÍ AUTOMATICKY! !!!" << std::endl;
                std::cout << "<<< Dostal jsi " << damage << " damage! Tvoje HP: "
                          << m_player.getHealth() << "/" << m_player.getMaxHealth() << "\n" << std::endl;

                // Kontrola smrti hráče
                if (m_player.getHealth() <= 0) {
                    std::cout << "\n=== GAME OVER ===" << std::endl;
                    std::cout << "Byl jsi poražen " << m_currentEnemy->getName() << "em!" << std::endl;
                    m_running = false;
                }

                // Re-render po útoku enemy
                m_renderEngine.render(m_player, m_renderEngine.getCamera(),
                                    m_levelLogic->getCurrentLevel(),
                                    m_levelLogic->getCurrentMap());
            }
        }
    }
}

Vec2 Game::getSpawnAtEntry(ExitDirection entryDir) const {
    Map* map = m_levelLogic->getCurrentMap();
    int centerX = map->getWidth() / 2;
    int centerY = map->getHeight() / 2;

    switch (entryDir) {
        case ExitDirection::North:
            return Vec2(centerX, 2); // Kousek od horního okraje
        case ExitDirection::South:
            return Vec2(centerX, map->getHeight() - 3);
        case ExitDirection::East:
            return Vec2(map->getWidth() - 3, centerY);
        case ExitDirection::West:
            return Vec2(2, centerY);
    }
    return Vec2(centerX, centerY);
}

Vec2 Game::getSpawnAtExit(ExitDirection exitDir) const {
    Map* map = m_levelLogic->getCurrentMap();
    int centerX = map->getWidth() / 2;
    int centerY = map->getHeight() / 2;

    switch (exitDir) {
        case ExitDirection::North:
            return Vec2(centerX, 2);
        case ExitDirection::South:
            return Vec2(centerX, map->getHeight() - 3);
        case ExitDirection::East:
            return Vec2(map->getWidth() - 3, centerY);
        case ExitDirection::West:
            return Vec2(2, centerY);
    }
    return Vec2(centerX, centerY);
}