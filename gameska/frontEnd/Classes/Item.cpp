//
// Created by elisk on 19.11.2025.
//

#include "item.h"

Item::Item(string name, string type, int bonusPower)
    : m_name(name), m_type(type), m_bonusPower(bonusPower){
}


string Item::getName() const{
return m_name;
}

string Item::getType() const{
return m_type;
}

int Item::getBonusPower() const{
return m_bonusPower;
}