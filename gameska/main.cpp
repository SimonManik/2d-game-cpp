//import modulu
#include "backEnd/gameLogic/Game.h"
#include "backEnd/render/TerminalUtils.h"
#include "frontEnd/Classes/Menu/MainMenuDesign.h"

int main() {
    auto [SCREEN_W, SCREEN_H] = TerminalUtils::getTerminalSize();


    while (true) {
        MainMenuDesign menu;

        // kdyz menu vrati true ukonci se hra
        if (!menu.run()) {
            break;
        }

        // kdyz menu vrati true spusti se hra
        Game game(SCREEN_W, SCREEN_H);
        game.run();

    }

    return 0;
}