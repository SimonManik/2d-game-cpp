//
// Created by elisk on 10.12.2025.
//

#ifndef GAMESKA_WEAPON_H
#define GAMESKA_WEAPON_H


#include "Item.h"

// Weapon inherits from Item
class Weapon : public Item {
public:
    /

    Weapon(const std::string& name, int bonusPower);  // Parametric Constructor


    std::string getDescription() const override;  // Override the description function
};

#endif //GAMESKA_WEAPON_H