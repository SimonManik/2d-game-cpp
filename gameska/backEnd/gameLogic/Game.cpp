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

    // inicializace
    m_levelLogic->nextLevel();
    Map* currentMap = m_levelLogic->getCurrentMap();
    if (currentMap != nullptr) {
        m_player.setPosition(currentMap->getSpawnPoint());
    }
    m_renderEngine.getCamera().setPosition(m_player.getPosition());
    m_renderEngine.render(m_player, m_renderEngine.getCamera());

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
        m_renderEngine.render(m_player, m_renderEngine.getCamera(), m_levelLogic->getCurrentMap());
    }

    std::cout << "x: " << m_player.getPosition().x << ", y:" << m_player.getPosition().y << std::endl;
    std::cout << m_levelLogic->getCurrentLevel() << std::endl;
}

void Game::update(Command cmd) {
    Vec2 oldPos = m_player.getPosition();

    // vypocet nove pozice bez fyzickeho pohybu
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
        // kontrola, zda je cilova pozice platna
        if (!currentMap->isWalkable(newPos)) {
            return;
        }

        // kontrola trapdooru pred pohybem
        if (currentMap->getDisplayChar(newPos) == 'O') {
            m_levelLogic->nextLevel();
            currentMap = m_levelLogic->getCurrentMap();
            if (currentMap != nullptr) {
                m_player.setPosition(currentMap->getSpawnPoint());
                m_renderEngine.getCamera().setPosition(m_player.getPosition());
            }
            return;
        }
    }

    // pokud vse proslo, teprve se hrac pohne
    m_player.setPosition(newPos);
    m_renderEngine.getCamera().setPosition(m_player.getPosition());
}