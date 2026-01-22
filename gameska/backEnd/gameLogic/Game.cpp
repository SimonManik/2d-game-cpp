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


Game::Game(int screenW, int screenH)
    : m_renderEngine(screenW, screenH)
    , m_inputHandler()
    , m_player(Vec2(0, 0))
    , m_levelLogic(nullptr)
    , m_running(false) {
    m_levelLogic = new LevelLogic();
}

Game::~Game() {
    delete m_levelLogic;
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
            }
            return;
        }
    }

    // Pokud vše prošlo, teprve se hráč pohne
    m_player.setPosition(newPos);
    m_renderEngine.getCamera().setPosition(m_player.getPosition());
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