//
// Created by Metoděj Janota on 11.11.2025.
//

#include "consoleBuffer.h"
#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <cstdio>
#endif

ConsoleBuffer::ConsoleBuffer(int width, int height): m_width(width), m_height(height) {
    buffer.resize(height, std::vector<char>(width, ' '));

    #ifdef _WIN32
    #else
        std::system("clear");
    #endif
}

ConsoleBuffer::~ConsoleBuffer() {
    #ifdef _WIN32
    #endif
}

void ConsoleBuffer::clear() {
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            buffer[y][x] = ' ';
        }
    }
}

void ConsoleBuffer::setChar(int x, int y, char c) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) {
        return;
    }
    buffer[y][x] = c;
}

void ConsoleBuffer::display() {
#ifdef _WIN32
#else
    std::printf("\033[H");

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            std::putchar(buffer[y][x]);
        }
        if (y < m_height - 1) {
            std::putchar('\n');
        }
    }

    std::fflush(stdout);
    #endif
}