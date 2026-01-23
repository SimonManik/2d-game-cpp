//
// Created by Metoděj Janota on 24.11.2025.
//

#ifndef GAMESKA_GAME_H
#define GAMESKA_GAME_H

#include "../../frontEnd/Classes/Player.h"
#include "InputHandler.h"
#include "LevelLogic.h"
#include "../render/RenderEngine.h"

class Game {
public:
    Game(int screenW, int screenH);
    ~Game();
    void run();

private:
    void update(Command cmd);
    void spawnEnemyInCurrentRoom();
    void updateEnemyAI(float deltaTime);

    double m_totalTime = 0.0;
    float m_enemyAttackTimer = 0.0f;     // Potřebné pro AI
    float m_enemyAttackInterval = 5.0f;  // Interval útoku

    // modules
    RenderEngine m_renderEngine;
    InputHandler m_inputHandler;
    LevelLogic* m_levelLogic;

    // game objects
    Player m_player;
    Enemy* m_currentEnemy = nullptr;
    bool m_running;
    Vec2 getSpawnAtEntry(ExitDirection entryDir) const;
    Vec2 getSpawnAtExit(ExitDirection exitDir) const;
};

#endif //GAMESKA_GAME_H