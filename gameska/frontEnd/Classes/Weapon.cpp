//
// Created by elisk on 10.12.2025.
//

#include "Weapon.h"




Weapon::Weapon(const std::string& name, int bonusPower)
    : Item(name, "Weapon", bonusPower) {
}

std::string Weapon::getDescription() const {
    return "This is a weapon. Use it to deal damage.";
}