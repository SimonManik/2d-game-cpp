//
// Created by Metoděj Janota on 24.11.2025.
//

#ifndef GAMESKA_PLAYER_H
#define GAMESKA_PLAYER_H


#include "../../backEnd/types/Vec2.h"
#include "../../backEnd/types/Command.h"
#include "MainInheriteClass.h"
#include "../../backEnd/types/Color.h"

class Player : public MainInheriteClass {
private:
    // Proměnné pro správu životů, které bude zobrazovat tvůj HUD
    int m_health;
    int m_maxHealth;
    int m_attackDamage = 10;
    bool m_canAttack = true;
    float m_attackCooldown = 0.5f;

public:
    Player(Vec2 startPos)
    : MainInheriteClass(startPos, '@', Color::GREEN, ObjectType::Player)
    , m_health(100)    // Počáteční zdraví
    , m_maxHealth(100) // Maximální kapacita zdraví
    {}

    // Gettery pro UIRender, aby věděl, kolik životů vykreslit
    int getHealth() const { return m_health; }
    int getMaxHealth() const { return m_maxHealth; }

    // Metoda pro změnu zdraví (využitelná při boji nebo léčení)
    void changeHealth(int amount) {
        m_health += amount;
        if (m_health > m_maxHealth) m_health = m_maxHealth;
        if (m_health < 0) m_health = 0;
    }

    // Původní metody třídy Player
    void handleCommand(Command cmd);
    void update() override {}
    char getDisplayChar() const { return '@'; }

    // Combat
    int attack() {
        if (m_canAttack) {
            m_canAttack = false;
            return m_attackDamage;
        }
        return 0;
    }

    void resetAttack() { m_canAttack = true; }
};

#endif //GAMESKA_PLAYER_H