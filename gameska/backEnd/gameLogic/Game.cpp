//
// Created by Metoděj Janota on 24.11.2025.
//

#include "Game.h"
#include <chrono>
#include <cstdio>
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
    m_renderEngine.getCamera().setPosition(m_player.getPosition());
    m_renderEngine.render(m_player, m_renderEngine.getCamera());

    while (m_running) {
        if (!m_inputHandler.kbhit()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        Command cmd = m_inputHandler.getInput();

        if (cmd == Command::NONE) {
            continue;
        }

        if (cmd == Command::QUIT) {
            m_running = false;
            continue;
        }

        update(cmd);

        // render
        m_renderEngine.render(m_player, m_renderEngine.getCamera());
    }
}

void Game::update(Command cmd) {
    m_player.handleCommand(cmd);
    m_renderEngine.getCamera().setPosition(m_player.getPosition());

    // TODO: enemies, collisions,etc.
}