//
// Created by Metoděj Janota on 10.11.2025.
//

#ifndef ZOO_ZS2025_2026_XJANOTA3_RENDERENGINE_H
#define ZOO_ZS2025_2026_XJANOTA3_RENDERENGINE_H

#include "ConsoleBuffer.h"
#include "./Camera.h"
#include "../../frontEnd/Classes/Player.h"
#include "../gameLogic/LevelLogic.h"
#include <string>

class RenderEngine {
public:
    RenderEngine(int screenW, int screenH);
    ~RenderEngine();

    // main render metoda
    void render(const Player& player, const Camera& camera, int currentLevel, const Map* map = nullptr);

    // render UI
    // void renderStaticUI();
    //void renderTempUI();

    // kamera
    Camera& getCamera() { return m_camera; }
    const Camera& getCamera() const { return m_camera; }

private:
    void renderWorld(const Camera& camera, const Map* map);
    void renderPlayer(const Player& player, const Camera& camera);

    ConsoleBuffer m_buffer;
    Camera m_camera;
};

#endif //ZOO_ZS2025_2026_XJANOTA3_RENDERENGINE_H