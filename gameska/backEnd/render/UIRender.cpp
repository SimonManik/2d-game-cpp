#include "UIRender.h"
#include <string>

void UIRender::drawText(ConsoleBuffer& buffer, int x, int y, const std::string& text, Color color) {
    std::string ansi = ColorUtils::toAnsiCode(color);
    for (size_t i = 0; i < text.length(); ++i) {
        buffer.setChar(x + i, y, text[i], ansi);
    }
}

void UIRender::renderStaticUI(ConsoleBuffer& buffer, int hp, int maxHp, int level) {
    // 1. Level vpravo nahoře
    std::string lvlStr = "LVL: " + std::to_string(level);
    drawText(buffer, buffer.getWidth() - 10, 1, lvlStr, Color::YELLOW);

    // 2. HP Bar vlevo nahoře
    drawText(buffer, 2, 1, "HP: ", Color::WHITE);
    
    int barWidth = 15; // Trochu delší bar
    // Výpočet procentuálního zaplnění (ošetření dělení nulou)
    int filled = (maxHp > 0) ? (hp * barWidth) / maxHp : 0;

    for (int i = 0; i < barWidth; ++i) {
        char c = (i < filled) ? '#' : '-'; // Plný vs prázdný znak
        // Změna barvy podle stavu zdraví
        Color col;
        float hpPercent = (float)hp / maxHp;
        
        if (hpPercent > 0.5f) col = Color::GREEN;
        else if (hpPercent > 0.25f) col = Color::YELLOW;
        else col = Color::RED;

        buffer.setChar(6 + i, 1, c, ColorUtils::toAnsiCode(col));
    }
    
    // Číselná hodnota vedle baru (např. 80/100)
    std::string hpText = std::to_string(hp) + "/" + std::to_string(maxHp);
    drawText(buffer, 6 + barWidth + 1, 1, hpText, Color::WHITE);
}