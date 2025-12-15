//
// Created by Metoděj Janota on 09.12.2025.
//

#ifndef GAMESKA_LEVELLOGIC_H
#define GAMESKA_LEVELLOGIC_H


#include "../../frontEnd/Classes/Map.h"

class LevelLogic {
public:
    LevelLogic();
    ~LevelLogic();

    // Prejde na dalsi level
    void nextLevel();

    // Gettery
    float getScalePerLevel() const { return m_scalePerLevel; }
    Map* getCurrentMap() { return m_currentMap; }
    int getCurrentLevel () { return m_currentLevel; }

private:
    // nasledna implementace v enemy bude napr. "hp * (1 + scalePerLevel * (level - 1))" nebo stejne u damage
    float m_scalePerLevel;
    int m_currentLevel;
    Map* m_currentMap;

    void generateMap();
};

#endif //GAMESKA_LEVELLOGIC_H