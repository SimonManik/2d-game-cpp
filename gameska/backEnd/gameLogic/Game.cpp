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

Game::Game(int screenW, int screenH)
    : m_renderEngine(screenW, screenH)
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

        update(cmd);

        // render
        m_renderEngine.render(m_player, m_renderEngine.getCamera(), m_levelLogic->getCurrentMap());
    }

    std::cout << "x: " << m_player.getPosition().x << ", y:" << m_player.getPosition().y << std::endl;
    std::cout << m_levelLogic->getCurrentLevel() << std::endl;
}

void Game::update(Command cmd) {
    Vec2 oldPos = m_player.getPosition();
    m_player.handleCommand(cmd);
    Vec2 newPos = m_player.getPosition();

    Map* currentMap = m_levelLogic->getCurrentMap();
    if (currentMap != nullptr) {
        if (!currentMap->isWalkable(newPos)) {
            m_player.setPosition(oldPos);
            return;
        }

        // TODO: kontrola kolize s enemies
        // TODO: kontrola kolize s items
        // TODO: kontrola vstupu do trapdoor
    }

    m_renderEngine.getCamera().setPosition(m_player.getPosition());
}