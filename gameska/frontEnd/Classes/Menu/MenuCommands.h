//
// Created by manik on 13.12.2025.
//
#ifndef GAMESKA_MENUCOMMANDS_H
#define GAMESKA_MENUCOMMANDS_H

#include "CreditsScreen.h"
#include "StoryScreen.h"


class MenuCommand {
public:
    virtual ~MenuCommand() = default;
    virtual void execute() = 0;
};

// === konkretni prikazy ===

class PlayCommand : public MenuCommand {
    bool& startGameRef;
    bool& runningRef;
public:
    PlayCommand(bool& start, bool& run) : startGameRef(start), runningRef(run) {}

    void execute() override {
        startGameRef = true;
        runningRef = false;
    }
};

class CreditsCommand : public MenuCommand {
    CreditsScreen& screenRef;
public:
    CreditsCommand(CreditsScreen& screen) : screenRef(screen) {}

    void execute() override {
        screenRef.show();
    }
};

class StoryCommand : public MenuCommand {
    StoryScreen& screenRef;
public:
    StoryCommand(StoryScreen& screen) : screenRef(screen) {}

    void execute() override {
        screenRef.show();
    }
};

class ExitCommand : public MenuCommand {
    bool& runningRef;
public:
    ExitCommand(bool& run) : runningRef(run) {}

    void execute() override {
        runningRef = false;
    }
};

#endif //GAMESKA_MENUCOMMANDS_H