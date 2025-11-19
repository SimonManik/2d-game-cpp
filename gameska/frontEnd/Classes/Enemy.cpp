//
// Created by elisk on 19.11.2025.
//

#include "enemy.h"


//Returns the name of the enemy
std::string Enemy::getName() const {
    return m_name;
}

//Returns the enemy's power level
int Enemy::getStrength() const {
    return m_strength;
}

//Checks ifd enemy is still alive
bool Enemy::isAlive() const {
    return m_Isalive;
}

void Enemy::takeDamage(int damage) {
    if (Damage >= m_strength) {
        m_Isalive = false;
    }
}
