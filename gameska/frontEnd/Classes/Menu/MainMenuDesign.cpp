//
// Created by manik on 11.12.2025.
//
#include "MainMenuDesign.h"
#include <iostream>
#include <conio.h>   // _getch()
#include <cstdlib>   // system("cls")
#include <windows.h> // Barvy

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// --- VYKRESLOVÁNÍ MENU ---
void MainMenuDesign::draw(int selectedOption) {
    system("cls");

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



void MainMenuDesign::showPlayScreen() {
    system("cls");
    std::cout << "\n\n   HRA BEZI... (Predstirej, ze zabijis monstra)\n\n";
    std::cout << "   [Zmackni cokoliv pro navrat do menu]";
    _getch();
}

void MainMenuDesign::showCreditsScreen() {
    system("cls");
    std::cout << "\n\n   === CREDITS ===\n\n";
    std::cout << "   Backend: Janota & Wolf\n";
    std::cout << "   Frontend: Manik & Nemcova\n\n";
    std::cout << "   [Zmackni cokoliv pro navrat]";
    _getch();
}

void MainMenuDesign::showStoryScreen() {
    system("cls");
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
void MainMenuDesign::run() {
    int selection = 0;
    bool running = true;

    while (running) {
        draw(selection); // Nakresli menu

        int key = _getch(); // Cekej na klavesu

        // Ovládání
        if (key == 'w' || key == 'W' || key == 72) {
            if (selection > 0) selection--;
        }
        else if (key == 's' || key == 'S' || key == 80) {
            if (selection < 3) selection++;
        }
        else if (key == 13) { // ENTER
            // Tady se rozhoduje, co se stane
            if (selection == 0) showPlayScreen();
            if (selection == 1) showCreditsScreen();
            if (selection == 2) showStoryScreen();
            if (selection == 3) running = false; // Ukončí smyčku -> konec programu
        }
    }
}