//
// Created by Metoděj Janota on 11.11.2025.
//

#ifndef GAMESKA_CONSOLEBUFFER_H
#define GAMESKA_CONSOLEBUFFER_H

#include <vector>

#ifdef _WIN32
    #include <windows.h>
#endif

class ConsoleBuffer {
    public:
        ConsoleBuffer(int width, int height);
        ~ConsoleBuffer();

        void clear();
        void setChar(int x, int y, char c);
        void display();

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

    private:
        int m_width;
        int m_height;
        std::vector<std::vector<char>> buffer;

    #ifdef _WIN32
    #endif
};

#endif //GAMESKA_CONSOLEBUFFER_H