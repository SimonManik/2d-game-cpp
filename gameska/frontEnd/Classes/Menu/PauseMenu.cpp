
#include "PauseMenu.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

PauseMenu::Action PauseMenu::show() {
    std::cout << "\n\n    === GAME PAUSED ===\n";
    std::cout << "    [SPACE]     Resume\n";
    std::cout << "    [BACKSPACE] Exit to Menu\n";
    std::cout << "    Choose: ";

    while (true) {
        int key = _getch();
        
        // mezernik
        if (key == 32) {
            return RESUME;
        }
        
        // Backspace
        if (key == 8) {
            return EXIT_TO_MENU;
        }
    }
}