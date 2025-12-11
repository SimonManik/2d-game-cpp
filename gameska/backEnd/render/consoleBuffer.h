//
// Created by Metoděj Janota on 11.11.2025.
//

#ifndef GAMESKA_CONSOLEBUFFER_H
#define GAMESKA_CONSOLEBUFFER_H

#include <vector>

#ifdef _WIN32
    #include <windows.h>
#endif

struct ColoredChar {
    char character;
    std::string color;

    ColoredChar() : character(' '), color("") {}
    ColoredChar(char c, std::string col = "") : character(c), color(col) {}
};

class ConsoleBuffer {
    public:
        ConsoleBuffer(int width, int height);
        ~ConsoleBuffer();

        void clear();
        void setChar(int x, int y, char c, std::string color = "");
        void display();

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

    private:
        int m_width;
        int m_height;
        std::vector<std::vector<ColoredChar>> buffer;

    #ifdef _WIN32
    #endif
};

#endif //GAMESKA_CONSOLEBUFFER_H