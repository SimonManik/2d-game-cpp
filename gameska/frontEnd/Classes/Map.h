#ifndef MAP_H
#define MAP_H

#include <vector>
#include "../../backEnd/types/Vec2.h"

class Enemy;

class Map {
public:
    Map(int width, int height);
    ~Map();

    // metody pro tiles
    bool isWalkable(Vec2 pos) const;
    bool isInBounds(Vec2 pos) const;
    bool isExitTile(Vec2 pos) const;
    char getDisplayChar(Vec2 pos) const;
    void setTile(Vec2 pos, char c);

    // spawn point
    Vec2 getSpawnPoint() const { return m_spawnPoint; }
    void setSpawnPoint(Vec2 pos) { m_spawnPoint = pos; }

    // ytrapDoor
    Vec2 getExitPoint() const { return m_exitPoint; }
    void setExitPoint(Vec2 pos) { m_exitPoint = pos; }
    bool hasExit() const { return m_hasExit; }

    // enemies
    void addEnemy(Enemy* e);
    std::vector<Enemy*>& getEnemies() { return m_enemies; }
    const std::vector<Enemy*>& getEnemies() const { return m_enemies; }

    // gettery
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }

private:
    int m_width;
    int m_height;
    std::vector<std::vector<char>> m_tiles;
    Vec2 m_spawnPoint;
    Vec2 m_exitPoint;
    bool m_hasExit;
    std::vector<Enemy*> m_enemies;
};

#endif //MAP_H