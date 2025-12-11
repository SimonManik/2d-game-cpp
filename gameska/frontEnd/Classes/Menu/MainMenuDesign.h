//
// Created by manik on 11.12.2025.
//
#ifndef MAINMENU_MAINMENUDESIGN_H
#define MAINMENU_MAINMENUDESIGN_H

class MainMenuDesign {
public:
    // Hlavní smyčka menu, vrací true pokud chce hrát, false pokud chce exit
    bool run();
private:
    // Vykreslení menu
    void draw(int selectedOption);

    // Nové funkce pro jednotlivé obrazovky (aby to nebylo v mainu)
    void showCreditsScreen();
    void showStoryScreen();
};

#endif //MAINMENU_MAINMENUDESIGN_H