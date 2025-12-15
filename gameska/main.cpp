//import modulu
#include "backEnd/gameLogic/Game.h"
#include "backEnd/render/TerminalUtils.h"
#include "frontEnd/Classes/Menu/MainMenuDesign.h"

int main() {
    auto [SCREEN_W, SCREEN_H] = TerminalUtils::getTerminalSize();
    MainMenuDesign menu;
    if (bool gameRun = menu.run()) {
        Game game(SCREEN_W, SCREEN_H);
        game.run();
    }

    return 0;
}