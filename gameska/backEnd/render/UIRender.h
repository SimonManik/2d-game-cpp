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
    //  metoda pro vypis textu
    static void drawText(ConsoleBuffer& buffer, int x, int y, const std::string& text, Color color) {
        std::string ansi = ColorUtils::toAnsiCode(color);
        for (int i = 0; i < text.length(); ++i) {
            buffer.setChar(x + i, y, text[i], ansi);
        }
    }

    static void renderStaticUI(ConsoleBuffer& buffer, int hp, int level) {
        // vykresleni Levelu vpravo nahore
        std::string lvlStr = "LEVEL: " + std::to_string(level);
        drawText(buffer, buffer.getWidth() - 15, 1, lvlStr, Color::YELLOW);

        // Vykreslení HP Baru vlevo nahore

        drawText(buffer, 2, 1, "HP: ", Color::WHITE);
        int barWidth = 10;
        int filled = (hp * barWidth) / 100;

        for (int i = 0; i < barWidth; ++i) {
            char c = (i < filled) ? '#' : '-';
            Color col = (hp > 30) ? Color::GREEN : Color::RED;
            buffer.setChar(6 + i, 1, c, ColorUtils::toAnsiCode(col));
        }
    }
};
#endif