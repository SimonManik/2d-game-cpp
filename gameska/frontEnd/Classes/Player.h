//
// Created by Metoděj Janota on 24.11.2025.
//

#ifndef GAMESKA_PLAYER_H
#define GAMESKA_PLAYER_H


#include "../../backEnd/types/Vec2.h"
#include "../../backEnd/types/Command.h"

class Player {
public:
    Player(Vec2 startPos);

    void handleCommand(Command cmd);

    Vec2 getPosition() const { return m_position; }
    void setPosition(Vec2 pos) { m_position = pos; }

    char getDisplayChar() const { return '@'; }

private:
    Vec2 m_position;
};

#endif //GAMESKA_PLAYER_H