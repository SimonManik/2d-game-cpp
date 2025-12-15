//
// Created by manik on 13.12.2025.
//
#include "CreditsScreen.h"
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

// Definice barev
const int COLOR_RED = 4;
const int COLOR_WHITE = 7;
const int COLOR_GRAY = 8;

// === POMOCNA FUNKCE PRO MAC (Simulace _getch) ===
#ifndef _WIN32
int _getch_credits() {
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

// POMOCNA FUNKCE PRO NASTAVENI BAREV (GLOBALNI V TOMTO SOUBORU)
// Toto pouzijeme v printLine i v CreditsScreen::setColor
void setLocalColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    switch(color) {
        case 4: std::cout << "\033[31m"; break;  // Cervena
        case 7: std::cout << "\033[0m";  break;  // Bila (Reset)
        case 8: std::cout << "\033[90m"; break;  // Seda
        default: std::cout << "\033[0m"; break;
    }
#endif
}

void CreditsScreen::show() {
    draw();
    #ifdef _WIN32
        _getch(); // ceka na stisk klavesy (Windows)
    #else
        _getch_credits(); // ceka na stisk klavesy (Mac)
    #endif
}

// Pomocna funkce pro vykresleni radku s textem a cervenymi okraji
void printLine(const std::string& text, int color) {
    setLocalColor(COLOR_RED); // Nastavi cervenou
    std::cout << "        |"; // Levy okraj (cerveny)

    setLocalColor(color); // Nastavi barvu textu

    // Ramecek ma vnitrni sirku 50 znaku, text zarovname na stred
    int width = 50;
    int paddingLeft = (width - text.length()) / 2;
    int paddingRight = width - paddingLeft - text.length();

    std::cout << std::string(paddingLeft, ' '); // Mezery vlevo
    std::cout << text;                          // Text
    std::cout << std::string(paddingRight, ' ');// Mezery vpravo

    setLocalColor(COLOR_RED); // Zpet na cervenou
    std::cout << "|" << std::endl; // Pravy okraj (cerveny)
}

void CreditsScreen::draw() {
    clearScreen();

    // --- VRSEK ---
    setColor(COLOR_RED);
    std::cout << "\n\n";
    // Cerveny prerusovany okraj
    std::cout << "        +--------------------------------------------------+\n";
    std::cout << "        |                                                  |\n";

    // Nadpis CREDITS (Cervene)
    printLine("CREDITS", COLOR_RED);

    std::cout << "        |                                                  |\n";
    std::cout << "        +--------------------------------------------------+\n";

    // --- OBSAH ---
    std::cout << "        |                                                  |\n";

    printLine("Backend: Janota & Wolf", COLOR_WHITE);
    printLine("Frontend: Manik & Nemcova", COLOR_WHITE);
    printLine("Art & Sound: Team", COLOR_WHITE);

    std::cout << "        |                                                  |\n";

    printLine("Made with C++ and Pain", COLOR_GRAY);

    std::cout << "        |                                                  |\n";
    std::cout << "        +--------------------------------------------------+\n";

    // Napoveda dole
    std::cout << "\n";
    setColor(COLOR_GRAY);
    // Zarovnani napovedy na stred (rucne)
    std::cout << "               [Press any key to return to menu]\n";
    setColor(COLOR_WHITE);
}

void CreditsScreen::setColor(int color) {
    setLocalColor(color);
}

void CreditsScreen::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}