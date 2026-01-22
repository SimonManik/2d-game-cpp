//
// Created by Metoděj Janota on 11.11.2025.
//

#include "ConsoleBuffer.h"
#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdio>
#endif

ConsoleBuffer::ConsoleBuffer(int width, int height)
    : m_width(width), m_height(height) {
    buffer.resize(height,  std::vector<ColoredChar>(width, ColoredChar()));
#ifdef _WIN32
    system("cls");
#else
     system("clear");
#endif
}

ConsoleBuffer::~ConsoleBuffer() = default;

void ConsoleBuffer::clear() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            buffer[y][x] = ColoredChar(' ', "");
        }
    }
}

void ConsoleBuffer::setChar(int x, int y, char c, std::string color) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return;
    }
    buffer[y][x] = ColoredChar(c, std::move(color));
}

void ConsoleBuffer::display() {
#ifdef _WIN32
    //nastaveni kurzoru na pozici (0, 0)  to same jako  printf("\033[H"); na unix like
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            // Pokud má znak barvu, použij ANSI escape sekvence
            if (!buffer[y][x].color.empty()) {
                std::printf("%s", buffer[y][x].color.c_str());
            }
            std::putchar(buffer[y][x].character);
            if (!buffer[y][x].color.empty()) {
                std::printf("\033[0m");  // Reset barvy
            }
        }
        if (y < m_height - 1) {
            std::putchar('\n');
        }
    }
    std::fflush(stdout);
#else
    std::printf("\033[H");

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            if (!buffer[y][x].color.empty()) {
                std::printf("%s", buffer[y][x].color.c_str());
            }
            std::putchar(buffer[y][x].character);
            if (!buffer[y][x].color.empty()) {
                std::printf("\033[0m");
            }
        }
        if (y < m_height - 1) {
            std::putchar('\n');
        }
    }

    std::fflush(stdout);
    #endif
}