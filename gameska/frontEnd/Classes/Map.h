#ifndef MAP_H
#define MAP_H

#include <vector>
#include "../../backEnd/types/Vec2.h"

class Enemy;

enum class ExitDirection {
    North,
    South,
    East,
    West
};

class Map {
public:
    Map(int width, int height);
    ~Map();

    // Metody pro tiles
    bool isWalkable(Vec2 pos) const;
    bool isInBounds(Vec2 pos) const;
    bool isExitTile(Vec2 pos) const;
    bool isRoomExit(Vec2 pos) const;
    bool isRoomEntry(Vec2 pos) const; // NOVÁ metoda
    char getDisplayChar(Vec2 pos) const;
    void setTile(Vec2 pos, char c);

    // Spawn point
    Vec2 getSpawnPoint() const { return m_spawnPoint; }
    void setSpawnPoint(Vec2 pos) { m_spawnPoint = pos; }

    // Trapdoor
    Vec2 getExitPoint() const { return m_exitPoint; }
    void setExitPoint(Vec2 pos) { m_exitPoint = pos; }

    // Enemies
    void addEnemy(Enemy* e);
    std::vector<Enemy*>& getEnemies() { return m_enemies; }

    // Gettery
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }


    // Getter pro aktuální východ a vchod
    ExitDirection getCurrentExit() const { return m_currentExit; }
    ExitDirection getCurrentEntry() const { return m_currentEntry; }

    // Generování pokoje s východy
    void generateRoom(bool hasTrapdoor, ExitDirection entryFrom, bool isFirstRoom = false);

private:
    int m_width;
    int m_height;
    std::vector<std::vector<char>> m_tiles;
    Vec2 m_spawnPoint;
    Vec2 m_exitPoint;
    std::vector<Enemy*> m_enemies;
    ExitDirection m_currentExit;
    ExitDirection m_currentEntry; // NOVÝ člen

    void createExit(ExitDirection dir);
    void createEntry(ExitDirection dir); // NOVÁ metoda
};

#endif //MAP_H