//
// Created by manik on 11.12.2025.
//
#ifndef GAMESKA_MAINMENUDESIGN_H
#define GAMESKA_MAINMENUDESIGN_H

#include <vector>
#include <string>
#include <map>

#include "CreditsScreen.h"
#include "StoryScreen.h"
#include "MenuCommands.h"

class MainMenuDesign {
public:
    MainMenuDesign();
    ~MainMenuDesign();

    bool run();

private:
    std::vector<std::string> options;
    int currentSelection;

    bool running;
    bool startGame;

    std::map<int, MenuCommand*> commands;

    CreditsScreen creditsScreen;
    StoryScreen storyScreen;

    void draw();

    // Zde už není setupWindow()

    void setColor(int color);
    void clearScreen();
    void printCentered(const std::string& text);
};

#endif //GAMESKA_MAINMENUDESIGN_H