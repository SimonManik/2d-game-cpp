//
// Created by Metoděj Janota on 24.11.2025.
//

#ifndef GAMESKA_PLAYER_H
#define GAMESKA_PLAYER_H


#include "../../backEnd/types/Vec2.h"
#include "../../backEnd/types/Command.h"
#include "mainInheriteClass.h"
#include "../../backEnd/types/Color.h"

class Player : public MainInheriteClass {
public:
    Player(Vec2 startPos)
    : MainInheriteClass(startPos, '@', Color::GREEN, ObjectType::Player) {
    }

    void handleCommand(Command cmd);
    void update() override {}
    char getDisplayChar() const { return '@'; }
};

#endif //GAMESKA_PLAYER_H