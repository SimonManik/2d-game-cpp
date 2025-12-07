//
// Created by Metoděj Janota on 24.11.2025.
//

#include "Player.h"

Player::Player(Vec2 startPos)
    : m_position(startPos){}

void Player::handleCommand(Command cmd) {
    switch (cmd) {
        case Command::MOVE_UP:
            m_position.y++;
            break;
        case Command::MOVE_DOWN:
            m_position.y--;
            break;
        case Command::MOVE_LEFT:
            m_position.x--;
            break;
        case Command::MOVE_RIGHT:
            m_position.x++;
            break;
        default:
            break;
    }
}