
#include "PauseMenu.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
static int _getch() {
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
    bool running = true;
    int currentSelection = 0;

    while (running) {
        draw(currentSelection); // vykresleni

        int key = _getch();
        if (key == 224) key = _getch(); // osetreni sipek na windows

        // ovladani
        if (key == 'w' || key == 'W' || key == 72) { // Nahoru
            if (currentSelection > 0) currentSelection--;
        }
        else if (key == 's' || key == 'S' || key == 80) { // Dolu

            // 2 moznosti: Resume a Exit to Menu
            if (currentSelection < 1) currentSelection++;
        }
        else if (key == 13 || key == 10) { // ENTER
             if (currentSelection == 0) {
                 return RESUME; //
             } else {
                 return EXIT_TO_MENU;
             }
        }
        else if (key == 8 || key == 127) {
            return EXIT_TO_MENU;
        }
    }
    return RESUME;
}

void PauseMenu::draw(int selectedOption) {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << "\n\n";
    std::cout << "        +------------------+\n";
    std::cout << "        |    PAUSE MENU    |\n";
    std::cout << "        +------------------+\n";
    
    // moznost 1: resume
    if (selectedOption == 0) std::cout << "        > RESUME <\n";
    else std::cout << "          RESUME\n";

    // moznost 2: exit the game
    if (selectedOption == 1) std::cout << "        > EXIT TO MENU <\n";
    else std::cout << "          EXIT TO MENU\n";
    
}