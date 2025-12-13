//
// Created by manik on 13.12.2025.
//
#ifndef GAMESKA_CREDITSSCREEN_H
#define GAMESKA_CREDITSSCREEN_H

class CreditsScreen {
public:
    // zobrazi obrazovku a ceka na navrat
    void show();

private:
    void draw();
    void setColor(int color);
    void clearScreen();
};

#endif //GAMESKA_CREDITSSCREEN_H