//
// Created by manik on 11.12.2025.
//
#include "MainMenuDesign.h"
#include <iostream>

#ifdef _WIN32
    #include <conio.h> // _getch()
    #include <windows.h> // Barvy
#else
    #include <termios.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif

#ifndef _WIN32
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

void setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    switch(color) {
        case 4:  std::cout << "\033[31m"; break; // cervena
        case 7:  std::cout << "\033[37m"; break; // bila
        case 8:  std::cout << "\033[90m"; break; // seda
        case 15: std::cout << "\033[97m"; break; // vic bila
        default: std::cout << "\033[0m";  break; // Reset
    }
#endif
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// --- VYKRESLOVÁNÍ MENU ---
void MainMenuDesign::draw(int selectedOption) {
    clearScreen();

    setColor(4); // Červená
    std::cout << "\n\n";
    std::cout << "        +--------------------------------------------------+\n";
    std::cout << "        |                PAIN  &  SUFFERING                |\n";
    std::cout << "        +--------------------------------------------------+\n";
    std::cout << "\n";

    // Play
    if (selectedOption == 0) { setColor(15); std::cout << "                  >>   PLAY GAME   <<\n"; }
    else                     { setColor(7);  std::cout << "                       Play Game\n"; }

    // Credits
    if (selectedOption == 1) { setColor(15); std::cout << "                  >>    CREDITS    <<\n"; }
    else                     { setColor(7);  std::cout << "                        Credits\n"; }

    // Story
    if (selectedOption == 2) { setColor(15); std::cout << "                  >>     STORY     <<\n"; }
    else                     { setColor(7);  std::cout << "                         Story\n"; }

    // Exit
    if (selectedOption == 3) { setColor(15); std::cout << "                  >>     EXIT      <<\n"; }
    else                     { setColor(7);  std::cout << "                         Exit\n"; }

    std::cout << "\n";
    setColor(8);
    std::cout << "        Use W/S to move, ENTER to select\n";
    setColor(7);
}

void MainMenuDesign::showCreditsScreen() {
    clearScreen();
    std::cout << "\n\n   === CREDITS ===\n\n";
    std::cout << "   Backend: Janota & Wolf\n";
    std::cout << "   Frontend: Manik & Nemcova\n\n";
    std::cout << "   [Zmackni cokoliv pro navrat]";
    _getch();
}

void MainMenuDesign::showStoryScreen() {
    clearScreen();
    std::cout << "\n\n   === STORY ===\n\n";
    std::cout << "     In a world full of pain and suffering...\n";
    std::cout << "   Pozor na vlaky.\n\n";
    std::cout << "   And don't forget, there's light at";
    std::cout << "   the end of the tunnel, but be careful  ";
    std::cout << "    it's not an oncoming train... ";
    std::cout << "   It all depends on YOU... ";
    _getch();
}

// --- HLAVNÍ SMYČKA ---
bool MainMenuDesign::run() {
    int selection = 0;
    bool running = true;

    while (running) {
        draw(selection);
        int key = _getch();
        bool keyHandled = false;

#ifdef _WIN32
        // windows sipky
        if (key == 224) {
            key = _getch();
            if (key == 72 && selection > 0) {
                selection--;
                keyHandled = true;
            }
            else if (key == 80 && selection < 3) {
                selection++;
                keyHandled = true;
            }
        }
#else
        // unix sipky
        if (key == 27) {
            _getch();
            key = _getch();
            if (key == 65 && selection > 0) {
                selection--;
                keyHandled = true;
            }
            else if (key == 66 && selection < 3) {
                selection++;
                keyHandled = true;
            }
        }
#endif
        if (!keyHandled) {
            if (key == 'w' || key == 'W') {
                if (selection > 0) selection--;
            }
            else if (key == 's' || key == 'S') {
                if (selection < 3) selection++;
            }
            else if (key == 13 || key == 10) {
                if (selection == 0) {
                    clearScreen();
                    return true; // Spustit hru
                }
                if (selection == 1) showCreditsScreen();
                if (selection == 2) showStoryScreen();
                if (selection == 3) return false; // Ukončit program
            }
        }
    }
    return false;
}