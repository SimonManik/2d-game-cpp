//
// Created by elisk on 25.11.2025.
//

#ifndef GAMESKA_RAT_H
#define GAMESKA_RAT_H

#include "Enemy.h"

class Rat: public Enemy {

public:

    Rat() : Enemy("Rat", 10, true, 25) {
    }

    Rat(const int m_strength, const int m_health):Enemy ("Rat", m_strength, true, m_health) {}

    ~Rat() override {}


    void attack() const override;
};


#endif //GAMESKA_RAT_H