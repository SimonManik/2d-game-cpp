//
// Created by Metoděj Janota on 23.11.2025.
//

#include "InputHandler.h"
#include <iostream>
#include <thread>

InputHandler::InputHandler() {
#ifndef _WIN32
#endif
}

InputHandler::~InputHandler() {
#ifndef _WIN32
#endif
}

bool InputHandler::kbhit() {
#ifdef _WIN32
#else
    int ch = ::getchar();
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
#endif
}

char InputHandler::getch() {
#ifdef _WIN32
#else
    return ::getchar();
#endif
}

Command InputHandler::getInput() {
    char key = getch();
    Command cmd = Command::NONE;

    switch (key) {
        case 'w': case 'W':
            cmd = Command::MOVE_UP;
            break;
        case 's': case 'S':
            cmd = Command::MOVE_DOWN;
            break;
        case 'a': case 'A':
            cmd = Command::MOVE_LEFT;
            break;
        case 'd': case 'D':
            cmd = Command::MOVE_RIGHT;
            break;
        case 27:
            cmd = Command::QUIT;
            break;
        default:
            break;
    }

    return cmd;
}
