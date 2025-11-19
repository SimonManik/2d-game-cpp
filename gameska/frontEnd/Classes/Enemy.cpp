//
// Created by elisk on 19.11.2025.
//

#include "enemy.h"



std::string Enemy::getName() const {  //Returns the name of the enemy
    return m_name;
}


int Enemy::getStrength() const {  //Returns the enemy's power level
    return m_strength;
}


bool Enemy::isAlive() const {   //Checks if enemy is still alive
    return m_Isalive;
}

void Enemy::takeDamage(int damage) {
    if (Damage >= m_strength) {
        m_Isalive = false;
    }
}
