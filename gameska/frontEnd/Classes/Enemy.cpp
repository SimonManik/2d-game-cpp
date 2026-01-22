//
// Created by elisk on 19.11.2025.
//

#include "Enemy.h"
#include <iostream>

Enemy::Enemy(string name, int strength, bool isAlive, int health, int level)
    : MainInheriteClass(Vec2(0, 0), 'E', Color::RED, ObjectType::Enemy)
    , m_name(name)
    , m_strength(strength)
    , m_isAlive(isAlive)
    , m_health(health)
    , m_damage(5 + (level - 1))
    , m_attackCooldown(1.5f)
    , m_timeSinceLastAttack(1.5f) {
}

void Enemy::update(float deltaTime) {
    m_timeSinceLastAttack += deltaTime;
}


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
    if (m_health <= 0) {
        m_health = 0;
        m_isAlive = false;  // Nastavit enemy jako mrtvého
    }

    std::cout << m_name << " took " << damage << " damage. HP left: " << m_health << std::endl;
}


void Enemy::move(const string direction) const {
    std::cout << m_name << " moves the " << direction << "anywhere" << std::endl;
}

int Enemy::attack() {
    // Vždy vrátí damage - cooldown řídí Game.cpp
    return m_damage;
}

void Enemy::setPosition(const Vec2& pos) {
    MainInheriteClass::m_position = pos;  // Explicitně použít rodičovskou m_position
}




