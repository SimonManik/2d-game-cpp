//
// Created by elisk on 19.11.2025.
//

#ifndef ZOO_ZS2025_2026_XJANOTA3_ENEMY_H
#define ZOO_ZS2025_2026_XJANOTA3_ENEMY_H
#include <string>

using namespace std;

class Enemy {
private:
    string m_name;
    int m_strength;
    bool m_isAlive;


public:
    Enemy(string m_name, int m_strength, bool m_isAlive)
    : m_name(m_name), m_strength(m_strength), m_isAlive(m_isAlive) {
    }// constructor

    string getName() const;    //getters
    int getStrength() const;
    bool isAlive() const;

    void takeDamage(int damage);    //methods
    //void dealDamage(int damage);  to do
    //void move(string direction);  to do



};


#endif //ZOO_ZS2025_2026_XJANOTA3_ENEMY_H