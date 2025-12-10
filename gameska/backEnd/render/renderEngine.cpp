//
// Created by Metoděj Janota on 10.11.2025.
//

#include "renderEngine.h"

RenderEngine::RenderEngine(int screenW, int screenH)
    : m_buffer(screenW, screenH)
    , m_camera(screenW, screenH) {
}

RenderEngine::~RenderEngine() {
}

void RenderEngine::render(const Player& player, const Camera& camera) {
    m_buffer.clear();

    // render game world
    renderWorld(player, camera);

    // render player
    renderPlayer(player, camera);

    // UIs
    //renderTempUI();
    //renderStaticUI();

    m_buffer.display();
}

void RenderEngine::renderWorld(const Player& player, const Camera& camera) {
    // TODO: implementace -> MapLogic -> Map a jednotlive bloky
}

void RenderEngine::renderPlayer(const Player& player, const Camera& camera) {
    Vec2 playerScreen = camera.worldToScreen(player.getPosition());
    if (camera.isVisible(player.getPosition())) {
        m_buffer.setChar(playerScreen.x, playerScreen.y, player.getDisplayChar());
    }
}

// TODO: pozdeji nejak poresit napriklad otevreni dvou tempUI naraz(vlaknama/boolem)

//void RenderEngine::renderStaticUI() {
    // TODO: static UI - hp
//}

//void RenderEngine::renderTempUI() {
    // TODO: implementovat
    // example: chest interakce
//}