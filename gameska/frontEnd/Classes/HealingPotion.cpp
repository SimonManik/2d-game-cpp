//
// Created by elisk on 10.12.2025.
//

#include "HealingPotion.h"

HealingPotion::HealingPotion(const std::string& name, int healingAmount)
    : Item(name, "Healing Potion", 0), m_healingAmount(healingAmount){
}

int HealingPotion::getHealingAmount() const {
    return m_healingAmount;
}

std::string HealingPotion::getDescription() const {
    return getName() + " (Heals " + std::to_string(m_healingAmount) + " HP)";
}


