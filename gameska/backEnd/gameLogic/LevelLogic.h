#ifndef GAMESKA_LEVELLOGIC_H
#define GAMESKA_LEVELLOGIC_H

#include "../../frontEnd/Classes/Map.h"
#include <vector>

struct RoomState {
    Map* map;
    ExitDirection exitDirection;
    int roomNumber;
};

class LevelLogic {
public:
    LevelLogic();
    ~LevelLogic();

    // Přejde na další místnost
    void nextRoom();

    // Vrátí se do předchozí místnosti
    void previousRoom();

    // Přejde na další level
    void nextLevel();

    // Gettery
    float getScalePerLevel() const { return m_scalePerLevel; }
    Map* getCurrentMap() { return m_currentMap; }
    int getCurrentLevel() const { return m_currentLevel; }
    int getCurrentRoom() const { return m_currentRoom; }
    bool canGoBack() const { return m_currentRoom > 1; }

private:
    float m_scalePerLevel;
    int m_currentLevel;
    int m_currentRoom; // 1-10
    Map* m_currentMap;
    ExitDirection m_lastExitDirection;

    // Historie místností pro možnost návratu
    std::vector<RoomState> m_roomHistory;

    void generateMap();
    ExitDirection getOppositeDirection(ExitDirection dir);
    ExitDirection getRandomExitExcluding(ExitDirection exclude1, ExitDirection exclude2);
};

#endif //GAMESKA_LEVELLOGIC_H