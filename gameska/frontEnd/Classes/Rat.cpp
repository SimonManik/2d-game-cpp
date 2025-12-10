//
// Created by elisk on 25.11.2025.
//

#include "Rat.h"
#include <iostream>

void Rat::attack() const {
    // replaces the generic Enemy::attack()
    std::cout << "The rat attacks with tail for  " << m_strength << " damage!" << std::endl;

}