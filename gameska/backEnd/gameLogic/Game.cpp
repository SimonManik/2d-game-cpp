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

    // inicializace
    m_levelLogic->nextLevel();
    Map* currentMap = m_levelLogic->getCurrentMap();
    if (currentMap != nullptr) {
        m_player.setPosition(currentMap->getSpawnPoint());
        Vec2 enemyPos = currentMap->getSpawnPoint();
        enemyPos.x += 5;  // Posun od hráče
        m_currentEnemy = new Enemy("Goblin", 10, true, 50, m_levelLogic->getCurrentLevel());
        m_currentEnemy->setPosition(enemyPos);
    }
    m_renderEngine.getCamera().setPosition(m_player.getPosition());
    m_renderEngine.render(m_player, m_renderEngine.getCamera(), m_levelLogic->getCurrentLevel(),
    m_levelLogic->getCurrentMap());
    while (m_running) {

        if (!m_inputHandler.kbhit()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        Command cmd = m_inputHandler.getInput();

        if (cmd == Command::NONE) continue;
        if (cmd == Command::QUIT) {
            m_running = false;
            continue;
        }
        
        if (cmd == Command::PAUSE) {  //pro pauz menu
            auto action = PauseMenu::show();
            if (action == PauseMenu::EXIT_TO_MENU) {
                m_running = false;
                continue;
            }
        }

        update(cmd);

        // render
        m_renderEngine.render(m_player, m_renderEngine.getCamera(), m_levelLogic->getCurrentLevel(),
        m_levelLogic->getCurrentMap());
    }

    std::cout << "x: " << m_player.getPosition().x << ", y:" << m_player.getPosition().y << std::endl;
    std::cout << m_levelLogic->getCurrentLevel() << std::endl;
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

                // Spawn noveho nepritele v nove arene
                delete m_currentEnemy;
                Vec2 newEnemyPos = currentMap->getSpawnPoint();
                newEnemyPos.x += 5;  // Posun od hráče
                m_currentEnemy = new Enemy("Goblin", 10, true, 50, m_levelLogic->getCurrentLevel());
                m_currentEnemy->setPosition(newEnemyPos);
                currentMap->addObject(m_currentEnemy);
            }
            return;
        }
    }

    // Pokud vše prošlo, teprve se hráč pohne
    m_player.setPosition(newPos);
    m_renderEngine.getCamera().setPosition(m_player.getPosition());

    //combat na mezerník
    if (cmd == Command::ATTACK && m_currentEnemy && m_currentEnemy->isAlive()) {
        Vec2 playerPos = m_player.getPosition();
        Vec2 enemyPos = m_currentEnemy->getPosition();

        // Kontrola vzdalenosti pro útok (max 2 políčka)
        int distance = abs(playerPos.x - enemyPos.x) + abs(playerPos.y - enemyPos.y);
        if (distance <= 2) {
            int damage = m_player.attack();
            if (damage > 0) {
                m_currentEnemy->takeDamage(damage);
                std::cout << "Útok! Enemy HP: " << m_currentEnemy->getHealth() << std::endl;
            }
        }
        return;  // Útok spotřebuje tah
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