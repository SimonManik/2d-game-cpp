//
// Created by elisk on 19.11.2025.
//

#include "Enemy.h"
#include <iostream>

Enemy::Enemy(string name, int strength, bool isAlive, int health, int level)
    : MainInheriteClass(Vec2(0, 0), 'E', Color::RED, ObjectType::Enemy)  // ZAVOLAT RODIČOVSKÝ KONSTRUKTOR
    , m_name(name)
    , m_strength(strength)
    , m_isAlive(isAlive)
    , m_health(health)
    , m_damage(5 + (level - 1))
    , m_attackCooldown(1.5f)
    , m_timeSinceLastAttack(1.5f)
    , m_position(Vec2(0, 0)) {
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
    if (m_health < 0) m_health = 0;

    std::cout << m_name << " took " << damage << " damage. HP left: " << m_health << std::endl;
}


void Enemy::move(const string direction) const {
    std::cout << m_name << " moves the " << direction << "anywhere" << std::endl;
}

int Enemy::attack() {
    if (m_timeSinceLastAttack >= m_attackCooldown) {
        m_timeSinceLastAttack = 0.0f;
        return m_damage;
    }
    return 0;
}

void Enemy::setPosition(const Vec2& pos) {
    m_position = pos;
}




