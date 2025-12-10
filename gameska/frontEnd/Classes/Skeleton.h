//
// Created by elisk on 25.11.2025.
//

#ifndef GAMESKA_SKELETON_H
#define GAMESKA_SKELETON_H

#include "Enemy.h"

class Skeleton : public Enemy {
private:
    int m_numArrows;

public:
    //pass specific stats to the parent
    Skeleton() : Enemy("Skeleton", 20, true, 50), m_numArrows(0) {
    }

    Skeleton(const int m_strength, const int m_health, const int m_numArrows) : Enemy("Skeleton", m_strength, true, m_health),
                                                                          m_numArrows(m_numArrows){
} //parametric const.

    ~Skeleton() override {}

    // override the attack
    void attack() const override;
};



#endif //GAMESKA_SKELETON_H