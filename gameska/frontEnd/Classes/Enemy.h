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

    Enemy(string name, int strength, bool isAlive, int health)
        : m_name(name), m_strength(strength), m_isAlive(isAlive), m_health(health) {
    }

    virtual ~Enemy()=default;

    string getName() const;    //getters
    int getStrength() const;
    bool isAlive() const;

    virtual void takeDamage(int damage);    //methods

    virtual void attack() const;

    virtual void move(string direction) const;

};


#endif //ZOO_ZS2025_2026_XJANOTA3_ENEMY_H