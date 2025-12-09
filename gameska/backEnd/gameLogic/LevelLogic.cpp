//
// Created by Metoděj Janota on 08.12.2025.
//

#include "LevelLogic.h"

LevelLogic::LevelLogic()
    : m_scalePerLevel(0.2f)
    , m_currentMap(nullptr)
    , m_currentLevel(1) {
    generateMap();
}

LevelLogic::~LevelLogic() {
    m_scalePerLevel += 0.2;
    m_currentLevel++;
    if (m_currentMap != nullptr) {
        delete m_currentMap;
    }
}

void LevelLogic::nextLevel() {
    if (m_currentMap != nullptr) {
        delete m_currentMap;
    }
    generateMap();
}

void LevelLogic::generateMap() {
    // zavola se generace mapy z Map
}