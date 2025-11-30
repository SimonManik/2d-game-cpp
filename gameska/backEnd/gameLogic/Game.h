//
// Created by Metoděj Janota on 24.11.2025.
//

#ifndef GAMESKA_GAME_H
#define GAMESKA_GAME_H

#include "./../render/consoleBuffer.h"
#include "../../frontEnd/Classes/Player.h"
#include "Camera.h"
#include "InputHandler.h"

class Game {
public:
    Game(int screenW, int screenH);
    void run();

private:
    void update();
    void render();

    // mopduly
    ConsoleBuffer m_buffer;
    Camera m_camera;
    InputHandler m_inputHandler;

    // game obj.
    Player m_player;
    bool m_running;
};


#endif //GAMESKA_GAME_H