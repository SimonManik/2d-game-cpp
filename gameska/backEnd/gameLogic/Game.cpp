//
// Created by Metoděj Janota on 24.11.2025.
//

#include "Game.h"
#include <chrono>
#include <cstdio>
#include <thread>
#include "./../types/Vec2.h"


Game::Game(int screenW, int screenH)
    : m_buffer(screenW, screenH)
    , m_camera(screenW, screenH)
    , m_player(Vec2(0, 0))
    , m_running(false) {
}

void Game::run() {
    m_running = true;
    m_camera.setPosition(m_player.getPosition());
    render();

    while (m_running) {
        Command cmd = m_inputHandler.getInput();

        if (cmd == Command::NONE) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        if (cmd == Command::QUIT) {
            m_running = false;
            continue;
        }

        m_player.handleCommand(cmd);
        m_camera.setPosition(m_player.getPosition());
        render();
    }
}

void Game::render() {
    m_buffer.clear();

    // grid
    for (int worldY = -50; worldY < 50; worldY += 5) {
        for (int worldX = -50; worldX < 50; worldX += 5) {
            Vec2 worldPos(worldX, worldY);

            if (m_camera.isVisible(worldPos)) {
                Vec2 screenPos = m_camera.worldToScreen(worldPos);
                m_buffer.setChar(screenPos.x, screenPos.y, '.');
            }
        }
    }

    // player uprostred
    Vec2 playerScreen = m_camera.worldToScreen(m_player.getPosition());
    m_buffer.setChar(playerScreen.x, playerScreen.y, m_player.getDisplayChar());

    // info o poz.,
    char info[100];
    sprintf(info, "Pos: (%d,%d)",
            m_player.getPosition().x,
            m_player.getPosition().y);

    for (int i = 0; info[i] != '\0' && i < m_buffer.getWidth(); i++) {
        m_buffer.setChar(i, 0, info[i]);
    }

    m_buffer.display();
}