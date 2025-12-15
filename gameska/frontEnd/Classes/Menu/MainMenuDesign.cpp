//
// Created by manik on 11.12.2025.
//
#include "MainMenuDesign.h"
#include <iostream>
#include <string>
#include <vector>

// podminene includovani knihoven
#ifdef _WIN32
    // Kód pro Windows
    #include <conio.h>
    #include <windows.h>
#else
    // kod pro Mac
    #include <termios.h>
    #include <unistd.h>
    #include <cstdlib> // Pro system("clear")
#endif

// Definice barev
const int COLOR_RED = 4;
const int COLOR_GRAY = 8;
const int COLOR_WHITE = 7;
const int COLOR_BRIGHT_WHITE = 15;

// pomocna funkce pro mac (Simulace _getch) =
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

MainMenuDesign::MainMenuDesign() {
    currentSelection = 0;
    running = true;
    startGame = false;

    options = {"Play Game", "Credits", "Story", "Exit"};

    //inicializace prikazu
    commands[0] = new PlayCommand(startGame, running);
    commands[1] = new CreditsCommand(creditsScreen);
    commands[2] = new StoryCommand(storyScreen);
    commands[3] = new ExitCommand(running);
}

MainMenuDesign::~MainMenuDesign() {
    for (auto& pair : commands) {
        delete pair.second;
    }
    commands.clear();
}

bool MainMenuDesign::run() {
    running = true;
    startGame = false;

    while (running) {
        draw();

        int key = _getch();
        if (key == 224) key = _getch(); // Ošetření šipek na Windows

        // ovladani
        if (key == 'w' || key == 'W' || key == 72) { // Nahoru
            if (currentSelection > 0) {
                currentSelection--;
                // ZVUK JEN NA WINDOWS
                #ifdef _WIN32
                Beep(600, 50);
                #endif
            }
        }
        else if (key == 's' || key == 'S' || key == 80) { // Dolu
            if (currentSelection < options.size() - 1) {
                currentSelection++;
                // ZVUK JEN NA WINDOWS
                #ifdef _WIN32
                Beep(600, 50);
                #endif
            }
        }
        else if (key == 13 || key == 10) { // ENTER (13 Win, 10 Mac)
            // ZVUK JEN NA WINDOWS
            #ifdef _WIN32
            Beep(800, 80);
            Beep(1000, 80);
            #endif

            if (commands.find(currentSelection) != commands.end()) {
                commands[currentSelection]->execute();
            }
        }
    }

    return startGame;
}

// GRAFIKA A VZHLED

void MainMenuDesign::draw() {
    clearScreen();

    setColor(COLOR_RED);
    std::cout << "\n\n";
    printCentered("+----------------------------------------------------------------+");
    printCentered("|                                                                |");

    printCentered("|                       ____   _   ___ _   _                     |");
    printCentered("|                      |  _ \\ / \\ |_ _| \\ | |                    |");
    printCentered("|                      | |_) / _ \\ | ||  \\| |                    |");
    printCentered("|                      |  __/ ___ \\| || |\\  |                    |");
    printCentered("|                      |_| /_/   \\_|_||_| \\_|                    |");
    printCentered("|                                                                |");

    printCentered("|                                &                               |");
    printCentered("|                                                                |");

    printCentered("|   ____  _   _  _____  _____  _____  ____   ___  _   _   ____   |");
    printCentered("|  / ___|| | | ||  ___||  ___|| ____||  _ \\ |_ _|| \\ | | / ___|  |");
    printCentered("|  \\___ \\| | | || |_   | |_   |  _|  | |_) | | | |  \\| || |  _   |");
    printCentered("|   ___) | |_| ||  _|  |  _|  | |___ |  _ <  | | | |\\  || |_| |  |");
    printCentered("|  |____/ \\___/ |_|    |_|    |_____||_| \\_\\|___||_| \\_| \\____|  |");
    printCentered("|                                                                |");

    setColor(COLOR_GRAY);
    printCentered("|                          [ RPG GAME ]                          |");

    setColor(COLOR_RED);
    printCentered("|                                                                |");
    printCentered("+----------------------------------------------------------------+");

    // --- stred ---
    printCentered("|                                          |");
    printCentered("+------------------------------------------+");

    for (size_t i = 0; i < options.size(); ++i) {
        std::string text;
        if (i == currentSelection) {
            setColor(COLOR_BRIGHT_WHITE);
            text = ">>  " + options[i] + "  <<";
        } else {
            setColor(COLOR_GRAY);
            text = options[i];
        }
        printCentered(text);
    }

    setColor(COLOR_RED);
    printCentered("+------------------------------------------+");

    // --- SPODEK ---
    std::cout << "\n";
    setColor(COLOR_GRAY);
    printCentered("[W/S] = move  |  [ENTER] = select");

    setColor(COLOR_WHITE);
}

// === pomocne FUNKCE (Cross-Platform) ===

void MainMenuDesign::clearScreen() {
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Mac/Linux
#endif
}

void MainMenuDesign::setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    // Mac verze (překlad na ANSI kódy)
    switch(color) {
        case 4: std::cout << "\033[31m"; break;  // cervena
        case 7: std::cout << "\033[0m";  break;  // Reset/bila
        case 8: std::cout << "\033[90m"; break;  // seda (Bright Black)
        case 15: std::cout << "\033[97m"; break; // jasne  bila
        default: std::cout << "\033[0m"; break;
    }
#endif
}

void MainMenuDesign::printCentered(const std::string& text) {
    int width = 80; // standartni sirka konzole
    int padding = (width - text.length()) / 2;
    if (padding > 0) std::cout << std::string(padding, ' ');
    std::cout << text << std::endl;
}