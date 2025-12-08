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
    // deklarace struktury pro ulozeni informaci o bufferu konzole
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // ziskani handle standardniho vystupu a naplneni struktury aktualnimi daty
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    // vypocet sirky viditelneho okna (rozdil praveho a leveho okraje + 1)
    int cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // vypocet vysky viditelneho okna (rozdil spodniho a horniho okraje + 1)
    int rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // vraceni vypocitanych rozmeru
    return {cols, rows};
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return {w.ws_col, w.ws_row};
#endif
}