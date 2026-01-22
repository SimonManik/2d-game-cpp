//
// Created by elisk on 19.11.2025.
//

#ifndef ZOO_ZS2025_2026_XJANOTA3_ENEMY_H
#define ZOO_ZS2025_2026_XJANOTA3_ENEMY_H
#include <string>

#include "MainInheriteClass.h"
#include "./../../backEnd/types/Vec2.h"
#include "./../../backEnd/types/Color.h"


using namespace std;

class Enemy : public MainInheriteClass
{
protected:
    string m_name;
    int m_strength;
    bool m_isAlive;
    int m_health;
    int m_damage;
    float m_attackCooldown = 1.5f;
    float m_timeSinceLastAttack = 0.0f;
    Vec2 m_position;

public:

    Enemy(string name, int strength, bool isAlive, int health, int level);

    virtual ~Enemy()=default;

    void setPosition(const Vec2& pos);

    string getName() const;    //getters
    int getStrength() const;
    bool isAlive() const;

    virtual void takeDamage(int damage);    //methods

    int attack();

    void update(float deltaTime);

    virtual void move(string direction) const;

    Vec2 getPosition() const {
        return m_position;
    }

    int getHealth() const {
        return m_health;
    }
    char getDisplayChar() const override { return 'E'; }

    std::string getColorAnsi() const override {
        return ColorUtils::toAnsiCode(Color::RED);
    }

    ObjectType getType() const override { return ObjectType::Enemy; }

    void update() override {
        // Nepotřebuje nic dělat pokud se enemy nepohybuje automaticky
    }

};


#endif //ZOO_ZS2025_2026_XJANOTA3_ENEMY_H