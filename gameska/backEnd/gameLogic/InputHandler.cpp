//
// Created by Metoděj Janota on 23.11.2025.
//

#include "InputHandler.h"
#include <iostream>
#include <thread>

#ifndef _WIN32
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#include <sys/time.h>

static struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
#endif

InputHandler::InputHandler() {
#ifndef _WIN32
    enableRawMode();
#endif
}

InputHandler::~InputHandler() {
#ifndef _WIN32
    disableRawMode();
#endif
}

bool InputHandler::kbhit() {
#ifdef _WIN32
    return _kbhit();
#else
    struct timeval tv = {0, 0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
#endif
}

char InputHandler::getch() {
#ifdef _WIN32
    return (char)_getch();
#else
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        return c;
    }
    return 0;
#endif
}

Command InputHandler::getInput() {
    char key = getch();

    if (key == 27) {
        return Command::PAUSE;
    }

    switch (key) {
        case 'w': case 'W':
            return Command::MOVE_UP;
        case 's': case 'S':
            return Command::MOVE_DOWN;
        case 'a': case 'A':
            return Command::MOVE_LEFT;
        case 'd': case 'D':
            return Command::MOVE_RIGHT;
        case 27: case 'q': case 'Q':
            return Command::QUIT;
        default:
            return Command::NONE;
    }
}