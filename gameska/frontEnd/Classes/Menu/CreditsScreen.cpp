#include "CreditsScreen.h"
#include <iostream>
#include <string>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdlib>
#endif

const int COLOR_RED = 4;
const int COLOR_WHITE = 7;
const int COLOR_GRAY = 8;

#ifndef _WIN32
static int _getch_credits() {
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

static void setLocalColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    switch(color) {
        case 4: std::cout << "\033[31m"; break;
        case 7: std::cout << "\033[0m";  break;
        case 8: std::cout << "\033[90m"; break;
        default: std::cout << "\033[0m"; break;
    }
#endif
}

static void printLine(const std::string& text, int color) {
    setLocalColor(COLOR_RED);
    std::cout << "        |";
    setLocalColor(color);
    int width = 50;
    int paddingLeft = (width - (int)text.length()) / 2;
    int paddingRight = width - paddingLeft - (int)text.length();
    std::cout << std::string(paddingLeft, ' ') << text << std::string(paddingRight, ' ');
    setLocalColor(COLOR_RED);
    std::cout << "|" << std::endl;
}

void CreditsScreen::show() {
    draw();
#ifdef _WIN32
    _getch();
#else
    _getch_credits();
#endif
}

void CreditsScreen::draw() {
    clearScreen();
    setLocalColor(COLOR_RED);
    std::cout << "\n\n        +--------------------------------------------------+\n";
    std::cout << "        |                                                  |\n";
    printLine("CREDITS", COLOR_RED);
    std::cout << "        |                                                  |\n";
    std::cout << "        +--------------------------------------------------+\n";
    std::cout << "        |                                                  |\n";
    printLine("Backend: Janota & Wolf", COLOR_WHITE);
    printLine("Frontend: Manik & Nemcova", COLOR_WHITE);
    printLine("Art & Sound: Team", COLOR_WHITE);
    std::cout << "        |                                                  |\n";
    printLine("Made with C++ and Pain", COLOR_GRAY);
    std::cout << "        |                                                  |\n";
    std::cout << "        +--------------------------------------------------+\n\n";
    setLocalColor(COLOR_GRAY);
    std::cout << "               [Press any key to return to menu]\n";
    setLocalColor(COLOR_WHITE);
}

void CreditsScreen::setColor(int color) { setLocalColor(color); }
void CreditsScreen::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}