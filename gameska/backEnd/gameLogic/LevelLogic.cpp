//
// Created by Metoděj Janota on 08.12.2025.
//

#include "LevelLogic.h"

LevelLogic::LevelLogic()
    : m_scalePerLevel(0.2f)
    , m_currentMap(nullptr)
    , m_currentLevel(0) {
    generateMap();
}

LevelLogic::~LevelLogic() {
    if (m_currentMap != nullptr) {
        delete m_currentMap;
    }
}

void LevelLogic::nextLevel() {
    m_scalePerLevel += 0.2f;
    m_currentLevel++;

    if (m_currentMap != nullptr) {
        delete m_currentMap;
    }
    generateMap();
}

void LevelLogic::generateMap() {
    //test mistnost 20x20
    m_currentMap = new Map(20, 20);

    // empty mistnost
    for (int y = 1; y < 19; y++) {
        for (int x = 1; x < 19; x++) {
            m_currentMap->setTile(Vec2(x, y), ' ');
        }
    }

    // Spawn point uprostřed
    Vec2 spawnPoint(10, 10);
    m_currentMap->setSpawnPoint(spawnPoint);
    m_currentMap->setTile(spawnPoint, 'S');

    // trapdoor v rohu
    Vec2 exitPoint(18, 18);
    m_currentMap->setExitPoint(exitPoint);
    m_currentMap->setTile(exitPoint, 'O');
}