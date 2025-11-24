//
// Created by Metoděj Janota on 24.11.2025.
//

#ifndef GAMESKA_VEC2_H
#define GAMESKA_VEC2_H

struct Vec2 {
    int x, y;
    Vec2(int x = 0, int y = 0) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    bool operator==(const Vec2& other) const {
        return x == other.x && y == other.y;
    }
};

#endif //GAMESKA_VEC2_H