//
// Created by elisk on 19.11.2025.
//

#ifndef ZOO_ZS2025_2026_XJANOTA3_ENEMY_H
#define ZOO_ZS2025_2026_XJANOTA3_ENEMY_H
#include <string>

using namespace std;

class Enemy {
protected:
    string m_name;
    int m_strength;
    bool m_isAlive;
    int m_health;

public:
    Enemy(const string &m_name, const int m_strength, const bool m_isAlive, const int m_health)
    : m_name(m_name), m_strength(m_strength), m_isAlive(m_isAlive), m_health(health) {
    }// constructor

    virtual ~Enemy()=default;

    string getName() const;    //getters
    int getStrength() const;
    bool isAlive() const;

    virtual void takeDamage(int damage);    //methods

    virtual void attack() const;

    virtual void move(string direction) const;

};


#endif //ZOO_ZS2025_2026_XJANOTA3_ENEMY_H