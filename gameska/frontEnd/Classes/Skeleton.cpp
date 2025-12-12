//
// Created by elisk on 25.11.2025.


#include "Skeleton.h"
#include <iostream>

void Skeleton::attack() const {

    std::cout << "The Skeleton shoots an arrow for " << m_strength << " damage!" << std::endl;

    if (m_numArrows > 0) {

        std::cout << "The Skeleton shoots an arrow for " << m_strength << " damage!" << std::endl;

    } else {
        std::cout << "The Skeleton is out of arrows" << std::endl;
    }
}


