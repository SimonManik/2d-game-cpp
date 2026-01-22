#include "Map.h"
#include "Enemy.h"
#include <random>

Map::Map(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_spawnPoint(0, 0)
    , m_exitPoint(0, 0)
    , m_currentExit(ExitDirection::North) {
    m_tiles.resize(height, std::vector<char>(width, '#'));
}

Map::~Map() {
    for (Enemy* e : m_enemies) {
        delete e;
    }
    m_enemies.clear();
}

bool Map::isInBounds(Vec2 pos) const {
    return pos.x >= 0 && pos.x < m_width &&
           pos.y >= 0 && pos.y < m_height;
}

bool Map::isWalkable(Vec2 pos) const {
    if (!isInBounds(pos)) return false;
    char tile = m_tiles[pos.y][pos.x];
    return tile == ' ' || tile == 'S' || tile == 'O';
}


bool Map::isRoomEntry(Vec2 pos) const {
    if (!isInBounds(pos)) return false;

    if (m_tiles[pos.y][pos.x] == ' ') {
        bool isOnEdge = (pos.x == 0 || pos.x == m_width - 1 ||
                         pos.y == 0 || pos.y == m_height - 1);

        if (!isOnEdge) return false;

        ExitDirection playerSide;
        if (pos.y == 0) playerSide = ExitDirection::North;
        else if (pos.y == m_height - 1) playerSide = ExitDirection::South;
        else if (pos.x == m_width - 1) playerSide = ExitDirection::East;
        else playerSide = ExitDirection::West;

        return playerSide == m_currentEntry;
    }
    return false;
}


bool Map::isRoomExit(Vec2 pos) const {
    if (!isInBounds(pos)) return false;

    if (m_tiles[pos.y][pos.x] == ' ') {
        bool isOnEdge = (pos.x == 0 || pos.x == m_width - 1 ||
                         pos.y == 0 || pos.y == m_height - 1);

        if (!isOnEdge) return false;

        ExitDirection playerSide;
        if (pos.y == 0) playerSide = ExitDirection::North;
        else if (pos.y == m_height - 1) playerSide = ExitDirection::South;
        else if (pos.x == m_width - 1) playerSide = ExitDirection::East;
        else playerSide = ExitDirection::West;

        return playerSide == m_currentExit;
    }
    return false;
}



bool Map::isExitTile(Vec2 pos) const {
    if (!isInBounds(pos)) return false;
    return m_tiles[pos.y][pos.x] == 'O';
}


char Map::getDisplayChar(Vec2 pos) const {
    if (!isInBounds(pos)) return ' ';
    return m_tiles[pos.y][pos.x];
}

void Map::setTile(Vec2 pos, char c) {
    if (isInBounds(pos)) {
        m_tiles[pos.y][pos.x] = c;
    }
}

void Map::addEnemy(Enemy* e) {
    if (e != nullptr) {
        m_enemies.push_back(e);
    }
}

void Map::createEntry(ExitDirection dir) {
    int centerX = m_width / 2;
    int centerY = m_height / 2;

    switch (dir) {
        case ExitDirection::North:
            for (int x = centerX - 2; x <= centerX + 2; ++x) {
                m_tiles[0][x] = (x == centerX - 2 || x == centerX + 2) ? 'e' : ' ';
            }
            break;
        case ExitDirection::South:
            for (int x = centerX - 2; x <= centerX + 2; ++x) {
                m_tiles[m_height - 1][x] = (x == centerX - 2 || x == centerX + 2) ? 'e' : ' ';
            }
            break;
        case ExitDirection::East:
            for (int y = centerY - 1; y <= centerY + 1; ++y) {
                m_tiles[y][m_width - 1] = (y == centerY - 1 || y == centerY + 1) ? 'e' : ' ';
            }
            break;
        case ExitDirection::West:
            for (int y = centerY - 1; y <= centerY + 1; ++y) {
                m_tiles[y][0] = (y == centerY - 1 || y == centerY + 1) ? 'e' : ' ';
            }
            break;
    }
}

void Map::createExit(ExitDirection dir) {
    int centerX = m_width / 2;
    int centerY = m_height / 2;

    switch (dir) {
        case ExitDirection::North:
            for (int x = centerX - 2; x <= centerX + 2; ++x) {
                m_tiles[0][x] = (x == centerX - 2 || x == centerX + 2) ? 'x' : ' ';
            }
            break;
        case ExitDirection::South:
            for (int x = centerX - 2; x <= centerX + 2; ++x) {
                m_tiles[m_height - 1][x] = (x == centerX - 2 || x == centerX + 2) ? 'x' : ' ';
            }
            break;
        case ExitDirection::East:
            for (int y = centerY - 1; y <= centerY + 1; ++y) {
                m_tiles[y][m_width - 1] = (y == centerY - 1 || y == centerY + 1) ? 'x' : ' ';
            }
            break;
        case ExitDirection::West:
            for (int y = centerY - 1; y <= centerY + 1; ++y) {
                m_tiles[y][0] = (y == centerY - 1 || y == centerY + 1) ? 'x' : ' ';
            }
            break;
    }
}

void Map::generateRoom(bool hasTrapdoor, ExitDirection entryFrom, bool isFirstRoom) {
    // Vyplň vše zdmi
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            m_tiles[y][x] = '#';
        }
    }

    // Vytvoř obdélníkový pokoj
    int wallThickness = 1;
    for (int y = wallThickness; y < m_height - wallThickness; ++y) {
        for (int x = wallThickness; x < m_width - wallThickness; ++x) {
            m_tiles[y][x] = ' ';
        }
    }

    // Spawn POUZE v první místnosti
    if (isFirstRoom) {
        Vec2 spawnPoint(m_width / 2, m_height / 2);
        m_spawnPoint = spawnPoint;
        m_tiles[spawnPoint.y][spawnPoint.x] = 'S';
    } else {
        m_spawnPoint = Vec2(m_width / 2, m_height / 2);
    }

    // Pokud je to 10. místnost - trapdoor
    if (hasTrapdoor) {
        Vec2 exitPoint(m_width / 2, m_height / 2 + 2);
        m_exitPoint = exitPoint;
        m_tiles[exitPoint.y][exitPoint.x] = 'O';

        // V 10. místnosti JE vchod (aby se dal vrátit)
        createEntry(entryFrom);
    } else {
        // Vytvoř VCHOD (KROMĚ první místnosti)
        if (!isFirstRoom) {
            createEntry(entryFrom);
        }

        // Vyber náhodný VÝCHOD
        std::random_device rd;
        std::mt19937 rng(rd());
        std::vector<ExitDirection> validExits;
        ExitDirection oppositeEntry;

        switch (entryFrom) {
            case ExitDirection::North: oppositeEntry = ExitDirection::South; break;
            case ExitDirection::South: oppositeEntry = ExitDirection::North; break;
            case ExitDirection::East: oppositeEntry = ExitDirection::West; break;
            case ExitDirection::West: oppositeEntry = ExitDirection::East; break;
        }

        // V první místnosti může být východ kamkoliv
        if (isFirstRoom) {
            for (int i = 0; i < 4; ++i) {
                validExits.push_back(static_cast<ExitDirection>(i));
            }
        } else {
            // V ostatních NE vstup ani jeho opak
            for (int i = 0; i < 4; ++i) {
                ExitDirection dir = static_cast<ExitDirection>(i);
                if (dir != entryFrom && dir != oppositeEntry) {
                    validExits.push_back(dir);
                }
            }
        }

        std::uniform_int_distribution<int> dirDist(0, validExits.size() - 1);
        ExitDirection exitDir = validExits[dirDist(rng)];

        m_currentExit = exitDir;
        m_currentEntry = entryFrom;
        createExit(exitDir);
    }
}