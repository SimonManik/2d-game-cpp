//
// Created by manik on 22.01.2026.
//

#ifndef GAMESKA_UIRENDER_H
#define GAMESKA_UIRENDER_H

#include <string>
#include "../../backEnd/render/ConsoleBuffer.h"
#include "../../backEnd/types/Color.h"

class UIRender {
public:
    static void drawText(ConsoleBuffer& buffer, int x, int y, const std::string& text, Color color);
    
    // parametr maxHp aby se bar správně počítal i když se zvýší maximální životy
    static void renderStaticUI(ConsoleBuffer& buffer, int hp, int maxHp, int level);

    static void drawBox(ConsoleBuffer& buffer, int x, int y, int w, int h) {
        std::string col = ColorUtils::toAnsiCode(Color::WHITE);
        // Vykresli rohy a čáry...
        // +------+
        // |      |
        // +------+
    }
};

#endif