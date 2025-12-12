//
// Created by elisk on 10.12.2025.
//

#ifndef GAMESKA_POTION_H
#define GAMESKA_POTION_H
#include "Item.h"

class HealingPotion : public Item {
private: int m_healingAmount;

public: HealingPotion(const std::string& name, int healingAmount);

int getHealingAmount()const;

std::string getDescription() const override;

};


#endif //GAMESKA_POTION_H