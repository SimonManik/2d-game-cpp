//import modulu
#include "backEnd/gameLogic/Game.h"

int main() {
    const int SCREEN_W = 80;
    const int SCREEN_H = 25;

    Game game(SCREEN_W, SCREEN_H);
    game.run();

    return 0;
}
