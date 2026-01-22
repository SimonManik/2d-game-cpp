#include "MainMenuDesign.h"
#include <iostream>
#include <string>
#include <vector>

// Podmíněné includování knihoven
#ifdef _WIN32
    // Kód pro Windows
    #include <conio.h>
    #include <windows.h>
    #include <mmsystem.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <cstdlib>
#endif

// Definice barev
const int COLOR_RED = 4;
const int COLOR_WHITE = 7;
const int COLOR_GRAY = 8;
const int COLOR_BRIGHT_WHITE = 15;
const int COLOR_NAVY = 1;

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

    // Inicializace příkazů [cite: 267-268]
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

    // Spuštění hudby pro MENU
#ifdef _WIN32
    PlaySound(TEXT("music/menu_theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
#endif

    while (running) {
        draw();

        int key = _getch();

        // Ošetření šipek a speciálních kláves
        if (key == 224 || key == 0) {
            key = _getch(); // Načtení kódu šipky (72 nahoru, 80 dolů)
        }

        // Ovládání - WASD + Šipky
        if (key == 'w' || key == 'W' || key == 72) {
            if (currentSelection > 0) {
                currentSelection--;
                #ifdef _WIN32
                Beep(600, 50); // Zvuková odezva pohybu [cite: 273-274]
                #endif
            }
        }
        else if (key == 's' || key == 'S' || key == 80) {
            if (currentSelection < (int)options.size() - 1) {
                currentSelection++;
                #ifdef _WIN32
                Beep(600, 50);
                #endif
            }
        }
        else if (key == 13 || key == 10) { // ENTER
            #ifdef _WIN32
            Beep(800, 80);
            Beep(1000, 80);
            #endif

            if (commands.find(currentSelection) != commands.end()) {
                commands[currentSelection]->execute();
            }
        }
    }

    // --- ZASTAVENÍ HUDBY ---
    // Při odchodu z menu do hry nebo ukončení hudbu vypneme
    #ifdef _WIN32
    PlaySound(NULL, 0, 0);
    #endif

    return startGame;
}

void MainMenuDesign::draw() {
    clearScreen();

    setColor(COLOR_RED);
    std::cout << "\n\n";
    printCentered("+----------------------------------------------------------------+");
    printCentered("|                                                                |");

    // ASCII ART - PAIN [cite: 281-285]
    setColor(COLOR_RED);
    printCentered("|                       ____   _   ___ _   _                     |");
    printCentered("|                      |  _ \\ / \\ |_ _| \\ | |                    |");
    printCentered("|                      | |_) / _ \\ | ||  \\| |                    |");
    printCentered("|                      |  __/ ___ \\| || |\\  |                    |");
    printCentered("|                      |_| /_/   \\_|_||_| \\_|                    |");
    printCentered("|                                                                |");

    setColor(COLOR_BRIGHT_WHITE);
    printCentered("|                                &                               |");

    // ASCII ART - SUFFERING [cite: 289-293]
    setColor(COLOR_NAVY);
    printCentered("|   ____  _   _  _____  _____  _____  ____   ___  _   _   ____   |");
    printCentered("|  / ___|| | | ||  ___||  ___|| ____||  _ \\ |_ _|| \\ | | / ___|  |");
    printCentered("|  \\___ \\| | | || |_   | |_   |  _|  | |_) | | | |  \\| || |  _   |");
    printCentered("|   ___) | |_| ||  _|  |  _|  | |___ |  _ \\  | | | |\\  || |_| |  |");
    printCentered("|  |____/ \\___/ |_|    |_|    |_____||_| \\_\\|___||_| \\_| \\____|  |");
    printCentered("|                                                                |");

    setColor(COLOR_GRAY);
    printCentered("|                          [ RPG GAME ]                          |");

    setColor(COLOR_RED);
    printCentered("|                                                                |");
    printCentered("+----------------------------------------------------------------+");
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

    std::cout << "\n";
    setColor(COLOR_NAVY);
    printCentered("[W/S] = move  |  [ENTER] = select");

    setColor(COLOR_WHITE);
}

void MainMenuDesign::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MainMenuDesign::setColor(int color) {
#ifdef _WIN32
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
    switch(color) {
        case 1: std::cout << "\033[34m"; break;
        case 4: std::cout << "\033[31m"; break;
        case 7: std::cout << "\033[0m";  break;
        case 8: std::cout << "\033[90m"; break;
        case 15: std::cout << "\033[97m"; break;
        default: std::cout << "\033[0m"; break;
    }
#endif
}

void MainMenuDesign::printCentered(const std::string& text) {
    int width = 80;
    int padding = (width - text.length()) / 2;
    if (padding > 0) std::cout << std::string(padding, ' ');
    std::cout << text << std::endl;
}