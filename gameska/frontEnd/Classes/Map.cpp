#include "Map.h"
#include "Enemy.h"

Map::Map(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_spawnPoint(0, 0)
    , m_exitPoint(0, 0)
    , m_hasExit(false) {

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
    if (!isInBounds(pos)) {
        return false;
    }

    char tile = m_tiles[pos.y][pos.x];
    return tile == ' ' || tile == 'S' || tile == 'T' || tile == 'O';
}

bool Map::isExitTile(Vec2 pos) const {
    if (!isInBounds(pos)) {
        return false;
    }
    return m_tiles[pos.y][pos.x] == 'O';
}

char Map::getDisplayChar(Vec2 pos) const {
    if (!isInBounds(pos)) {
        return ' ';
    }
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