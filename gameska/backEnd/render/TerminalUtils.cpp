//
// Created by Metoděj Janota on 06.12.2025.
//

//jindro - komentar s odkazem pro jistotu zatim nechcej, kazdopadne by ti mel stacit <windows.h>
//https://stackoverflow.com/questions/23369503/get-size-of-terminal-window-rows-columns

#include "TerminalUtils.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

std::pair<int, int> TerminalUtils::getTerminalSize() {
#ifdef _WIN32
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row};
#endif
}