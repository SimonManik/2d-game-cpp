//
// Created by elisk on 19.11.2025.
//

#include "Enemy.h"
#include <iostream>


std::string Enemy::getName() const {  //Returns the name of the enemy
    return m_name;
}


int Enemy::getStrength() const {  //Returns the enemy's power level
    return m_strength;
}


bool Enemy::isAlive() const {   //Checks if enemy is still alive
    return m_isAlive;
}

void Enemy::takeDamage(const int damage) {
    m_health -= damage;
    if (m_health < 0) m_health = 0;

    std::cout << m_name << " took " << damage << " damage. HP left: " << m_health << std::endl;
}

void Enemy::attack() const {
    // Default behavior
    std::cout << m_name << " attacks generically for " << m_strength << " damage!" << std::endl;
}

void Enemy::move(const string direction) const {
    std::cout << m_name << " moves the " << direction << "anywhere" << std::endl;
}




