//
// Created by elisk on 19.11.2025.
//

#ifndef ZOO_ZS2025_2026_XJANOTA3_ENEMY_H
#define ZOO_ZS2025_2026_XJANOTA3_ENEMY_H

using namespace std;

class Enemy {
private:
    string m_name;
    int m_strength;
    bool m_isAlive;


public:
    Enemy(string m_name, int m_strength, bool m_isAlive); // constructor

    string getName() const;    //getters
    int getStrength() const;
    bool isAlive() const;

    void takeDamage(int damage);    //methods
    void dealDamage(int damage);
    void move(string direction);



};


#endif //ZOO_ZS2025_2026_XJANOTA3_ENEMY_H