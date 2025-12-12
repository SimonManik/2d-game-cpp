//
// Created by elisk on 25.11.2025.
//

#ifndef GAMESKA_DRAGON_H
#define GAMESKA_DRAGON_H
#include "Enemy.h"

class Dragon : public Enemy {
public:
    Dragon() : Enemy("Dragon", 50, true, 100) {
    }

    Dragon(const int strength, const int health)
    : Enemy("Dragon", strength, true, health) {
    }

    ~Dragon() override {}

    void attack() const override;
};

#endif //GAMESKA_DRAGON_H