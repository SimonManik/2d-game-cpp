//
// Created by Metoděj Janota on 23.11.2025.
//

#ifndef GAMESKA_INPUTHANDLER_H
#define GAMESKA_INPUTHANDLER_H

#include "../types/Command.h"
#ifdef _WIN32
#include <windows.h>
#include <conio.h> // pro _kbhit() a _getch()
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
    bool kbhit();

private:
    char getch();
};


#endif //GAMESKA_INPUTHANDLER_H