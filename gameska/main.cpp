#include <iostream>

// import knihovny podle os
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

//import modulu
#include "backEnd//render//consoleBuffer.h"

int main() {
    // Pro rozliseni os
    #ifdef _WIN32
        std::cout << "Windows\n";
    #else
        std::cout << "Mac/Linux\n";
    #endif

    // Main.cpp
    ConsoleBuffer buffer(10, 10);
    buffer.clear();
    buffer.setChar(5, 5, '@');
    buffer.setChar(3, 3, '#');
    buffer.display();

    // end
    return 0;
}
