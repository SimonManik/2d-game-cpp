#include <iostream>

// import knihovny podle os
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

int main() {
    // Pro rozliseni os
    #ifdef _WIN32
        std::cout << "Windows\n";
    #else
        std::cout << "Mac/Linux\n";
    #endif

    // Main.cpp
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
