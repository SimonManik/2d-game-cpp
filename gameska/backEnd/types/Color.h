//
// Created by Metoděj Janota on 12.12.2025.
//

#ifndef GAMESKA_COLOR_H
#define GAMESKA_COLOR_H

#include <string>

enum class Color {
    BLACK,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
    RESET,
    NONE
};

class ColorUtils {
public:
    static std::string toAnsiCode(Color color) {
        switch (color) {
            case Color::BLACK:
                return "\033[30m";
            case Color::RED:
                return "\033[31m";
            case Color::GREEN:
                return "\033[32m";
            case Color::YELLOW:
                return "\033[33m";
            case Color::BLUE:
                return "\033[34m";
            case Color::MAGENTA:
                return "\033[35m";
            case Color::CYAN:
                return "\033[36m";
            case Color::WHITE:
                return "\033[37m";
            case Color::RESET:
                return "\033[0m";
            case Color::NONE:
                return "";
            default:
                return "";
        }
    }

    static std::string toString(Color color) {
        switch (color) {
            case Color::BLACK:
                return "BLACK";
            case Color::RED:
                return "RED";
            case Color::GREEN:
                return "GREEN";
            case Color::YELLOW:
                return "YELLOW";
            case Color::BLUE:
                return "BLUE";
            case Color::MAGENTA:
                return "MAGENTA";
            case Color::CYAN:
                return "CYAN";
            case Color::WHITE:
                return "WHITE";
            case Color::RESET:
                return "RESET";
            case Color::NONE:
                return "NONE";
            default:
                return "UNKNOWN";
        }
    }
};

#endif //GAMESKA_COLOR_H