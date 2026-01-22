#include "UIRender.h"
#include <string>

void UIRender::drawText(ConsoleBuffer& buffer, int x, int y, const std::string& text, Color color) {
    std::string ansi = ColorUtils::toAnsiCode(color);
    for (size_t i = 0; i < text.length(); ++i) {
        buffer.setChar(x + i, y, text[i], ansi);
    }
}

void UIRender::renderStaticUI(ConsoleBuffer& buffer, int hp, int maxHp, int level) {

    // 1. Level vpravo nahore
    std::string lvlStr = "LVL: " + std::to_string(level);
    drawText(buffer, buffer.getWidth() - 10, 1, lvlStr, Color::YELLOW);

    // 2. HP Bar vlevo nahore
    drawText(buffer, 2, 1, "HP: ", Color::WHITE);
    
    int barWidth = 15; // Trochu delsi bar

    //vypocet procentualniho zaplneni (osetreni deleni nulou)
    int filled = (maxHp > 0) ? (hp * barWidth) / maxHp : 0;

    for (int i = 0; i < barWidth; ++i) {
        char c = (i < filled) ? '#' : '-'; // plny vs prazdny znak

        // zmena barvy podle stavu zdravi
        Color col;
        float hpPercent = (float)hp / maxHp;
        
        if (hpPercent > 0.5f) col = Color::GREEN;
        else if (hpPercent > 0.25f) col = Color::YELLOW;
        else col = Color::RED;

        buffer.setChar(6 + i, 1, c, ColorUtils::toAnsiCode(col));
    }
    
    // hodnota vedle baru (napr. 80/100)
    std::string hpText = std::to_string(hp) + "/" + std::to_string(maxHp);
    drawText(buffer, 6 + barWidth + 1, 1, hpText, Color::WHITE);
}