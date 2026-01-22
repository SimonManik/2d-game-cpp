//
// Created by Metoděj Janota on 10.11.2025.
//

#include "RenderEngine.h"
#include "../types/Color.h"
#include "UIRender.h"

RenderEngine::RenderEngine(int screenW, int screenH)
    : m_buffer(screenW, screenH)
    , m_camera(screenW, screenH) {
}

RenderEngine::~RenderEngine() {
}

void RenderEngine::render(const Player& player, const Camera& camera, int currentLevel, int timeSeconds,const Map* map) {
    m_buffer.clear();

    // Render game world
    if (map != nullptr) {
        renderWorld(camera, map);
    }

    // Render player
    renderPlayer(player, camera);

    // UIs
    // vykresleni statickeho UI
    // Předáváme buffer a data z hráče/levelu (nyní včetně maxHealth)
    // UI se kresli jako posledni vrstva
    UIRender::renderStaticUI(m_buffer, player.getHealth(), player.getMaxHealth(), currentLevel);

    // docasne UI
    // renderTempUI(m_buffer, "Stiskni [E] pro interakci");

    m_buffer.display();
}

void RenderEngine::renderWorld(const Camera& camera, const Map* map) {
    Vec2 cameraPos = camera.getPosition();
    int halfW = camera.getViewportW() / 2;
    int halfH = camera.getViewportH() / 2;

    int startX = cameraPos.x - halfW;
    int endX = cameraPos.x + halfW;
    int startY = cameraPos.y - halfH;
    int endY = cameraPos.y + halfH;

    // tiles
    for (int worldY = startY; worldY <= endY; worldY++) {
        for (int worldX = startX; worldX <= endX; worldX++) {
            Vec2 worldPos(worldX, worldY);

            if (!map->isInBounds(worldPos)) {
                continue;
            }

            Vec2 screenPos = camera.worldToScreen(worldPos);

            if (screenPos.x >= 0 && screenPos.x < camera.getViewportW() &&
                screenPos.y >= 0 && screenPos.y < camera.getViewportH()) {

                char displayChar = map->getDisplayChar(worldPos);

                std::string color = "";
                if (displayChar == '#') {
                    color = ColorUtils::toAnsiCode(Color::WHITE);
                } else if (displayChar == '.') {
                    color = ColorUtils::toAnsiCode(Color::BLACK);  // nebo CYAN pro podlahu
                } else if (displayChar == 'S') {
                    color = ColorUtils::toAnsiCode(Color::GREEN);
                } else if (displayChar == 'T') {
                    color = ColorUtils::toAnsiCode(Color::YELLOW);
                }

                m_buffer.setChar(screenPos.x, screenPos.y, displayChar, color);

                }
        }
    }

    // Na konci renderWorld() za tiles
    // Vykresli všechny objekty v mapě
    for (const auto* obj : map->getObjects()) {
        if (!obj || obj->getType() == ObjectType::Player) continue;

        Vec2 worldPos = obj->getPosition();
        if (camera.isVisible(worldPos)) {
            Vec2 screenPos = camera.worldToScreen(worldPos);
            m_buffer.setChar(screenPos.x, screenPos.y,
                            obj->getDisplayChar(),
                            obj->getColorAnsi());
        }
}

}

void RenderEngine::renderPlayer(const Player& player, const Camera& camera) {
    Vec2 playerScreen = camera.worldToScreen(player.getPosition());
    if (camera.isVisible(player.getPosition())) {
        m_buffer.setChar(playerScreen.x, playerScreen.y,
                        player.getDisplayChar(),
                        player.getColorAnsi());
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