//import modulu
#include "backEnd/gameLogic/Game.h"
#include "backEnd/render/TerminalUtils.h"

int main() {
    auto [SCREEN_W, SCREEN_H] = TerminalUtils::getTerminalSize();

    Game game(SCREEN_W, SCREEN_H);
    game.run();

    return 0;
}