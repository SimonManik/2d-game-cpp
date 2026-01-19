#include "LevelLogic.h"
#include <random>

LevelLogic::LevelLogic()
    : m_scalePerLevel(0.2f)
    , m_currentMap(nullptr)
    , m_currentLevel(1)
    , m_currentRoom(1)
    , m_lastExitDirection(ExitDirection::North) {
    generateMap();
}

LevelLogic::~LevelLogic() {
    // Vyčisti historii
    for (RoomState& state : m_roomHistory) {
        if (state.map != nullptr) {
            delete state.map;
        }
    }
    m_roomHistory.clear();

    // Vyčisti aktuální mapu
    if (m_currentMap != nullptr) {
        delete m_currentMap;
    }
}

ExitDirection LevelLogic::getOppositeDirection(ExitDirection dir) {
    switch (dir) {
        case ExitDirection::North: return ExitDirection::South;
        case ExitDirection::South: return ExitDirection::North;
        case ExitDirection::East: return ExitDirection::West;
        case ExitDirection::West: return ExitDirection::East;
    }
    return ExitDirection::North;
}

ExitDirection LevelLogic::getRandomExitExcluding(ExitDirection exclude1, ExitDirection exclude2) {
    std::vector<ExitDirection> validDirections;

    // Projdi všechny směry a vyber ty, které nejsou zakázané
    for (int i = 0; i < 4; ++i) {
        ExitDirection dir = static_cast<ExitDirection>(i);
        if (dir != exclude1 && dir != exclude2) {
            validDirections.push_back(dir);
        }
    }

    // Vyber náhodný z povolených
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, validDirections.size() - 1);

    return validDirections[dist(rng)];
}

void LevelLogic::nextRoom() {
    // Ulož aktuální stav místnosti do historie
    RoomState currentState;
    currentState.map = m_currentMap;
    currentState.exitDirection = m_lastExitDirection;
    currentState.roomNumber = m_currentRoom;
    m_roomHistory.push_back(currentState);

    m_currentRoom++;

    // Pokud je to 10. místnost, nemění se směr (trapdoor)
    if (m_currentRoom <= 10) {
        m_lastExitDirection = m_currentMap->getCurrentExit();

        // Nová mapa se vytvoří
        m_currentMap = nullptr;
        generateMap();
    }
}

void LevelLogic::previousRoom() {
    if (!canGoBack()) return;

    // Smaž aktuální mapu (nevracíme se do ní)
    if (m_currentMap != nullptr) {
        delete m_currentMap;
        m_currentMap = nullptr;
    }

    // Obnov předchozí stav
    RoomState prevState = m_roomHistory.back();
    m_roomHistory.pop_back();

    m_currentMap = prevState.map;
    m_lastExitDirection = prevState.exitDirection;
    m_currentRoom = prevState.roomNumber;
}

void LevelLogic::nextLevel() {
    // Vyčisti historii předchozího levelu
    for (RoomState& state : m_roomHistory) {
        if (state.map != nullptr) {
            delete state.map;
        }
    }
    m_roomHistory.clear();

    m_scalePerLevel += 0.2f;
    m_currentLevel++;
    m_currentRoom = 1; // Reset místností
    m_lastExitDirection = ExitDirection::North;

    if (m_currentMap != nullptr) {
        delete m_currentMap;
    }
    generateMap();
}

void LevelLogic::generateMap() {
    m_currentMap = new Map(25, 15);

    bool hasTrapdoor = (m_currentRoom == 10);
    bool isFirstRoom = (m_currentRoom == 1);

    ExitDirection entryFrom = getOppositeDirection(m_lastExitDirection);

    m_currentMap->generateRoom(hasTrapdoor, entryFrom, isFirstRoom);
}