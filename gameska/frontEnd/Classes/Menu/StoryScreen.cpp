//
// Created by manik on 13.12.2025.
//
#include "StoryScreen.h"
#include <iostream>
#include <string>

// === PODMINENE INCLUDOVANI ===
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdlib>
#endif

// Konstanty barev - kvuli applu
const int COLOR_RED = 4;
const int COLOR_WHITE = 7;
const int COLOR_GRAY = 8;
const int COLOR_BRIGHT_WHITE = 15;

//  POMOCNA FUNKCE PRO MAC (Simulace _getch)
#ifndef _WIN32
int _getch_story() {
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

void StoryScreen::show() {
    draw();
    #ifdef _WIN32
        _getch();
    #else
        _getch_story();
    #endif
}

// Pomocna funkce pro nastaveni barev uvnitr tohoto souboru
void setStoryColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    switch(color) {
        case 4: std::cout << "\033[31m"; break;  // Cervena
        case 7: std::cout << "\033[0m";  break;  // Bila/Reset
        case 8: std::cout << "\033[90m"; break;  // Seda
        case 15: std::cout << "\033[97m"; break; // Jasne bila
        default: std::cout << "\033[0m"; break;
    }
#endif
}

void StoryScreen::draw() {
    clearScreen();

    // hlavicka story
    setColor(COLOR_RED);
    std::cout << "\n\n";
    std::cout << "        +--------------------------------------------------+\n";
    std::cout << "        |                                                  |\n";

    std::cout << "        |                      STORY                       |\n";

    std::cout << "        |                                                  |\n";
    std::cout << "        +--------------------------------------------------+\n";


    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "                                                  ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "     In a world full of pain and suffering...     ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "                                                  ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "     One hero will rise to face the darkness.     ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "   His journey will be full of danger and loss.   ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "                                                  ";
    setColor(COLOR_RED);   std::cout << "|\n";

    // Zvýraznění
    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_RED);   std::cout << "           Can he overcome PAIN & SUFFERING       ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "         and bring light back to this world?      ";
    setColor(COLOR_RED);   std::cout << "|\n";

    // Oddělovač
    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "                                                  ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_RED);   std::cout << "             -----------------------              ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "                                                  ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_GRAY);  std::cout << "       And don't forget, there's light at         ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_GRAY);  std::cout << "       the end of the tunnel, but be careful      ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_GRAY);  std::cout << "          it's not an oncoming train...           ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_WHITE); std::cout << "                                                  ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |";
    setColor(COLOR_BRIGHT_WHITE); std::cout << "             It all depends on YOU...             ";
    setColor(COLOR_RED);   std::cout << "|\n";

    setColor(COLOR_RED);   std::cout << "        |                                                  |\n";
    std::cout << "        +--------------------------------------------------+\n";

    std::cout << "\n";
    setColor(COLOR_GRAY);
    std::cout << "               [Press any key to return to menu]\n";
    setColor(COLOR_WHITE);
}

void StoryScreen::setColor(int color) {
    setStoryColor(color);
}

void StoryScreen::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}