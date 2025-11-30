//
// Created by Metoděj Janota on 23.11.2025.
//

#ifndef GAMESKA_INPUTHANDLER_H
#define GAMESKA_INPUTHANDLER_H

#include "../types/Command.h"
#ifdef _WIN32
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

class InputHandler {
public:
    InputHandler();
    ~InputHandler();
    Command getInput();

private:
    bool kbhit();
    char getch();
};


#endif //GAMESKA_INPUTHANDLER_H