//
// Created by elisk on 19.11.2025.
//

#include "Item.h"


Item::Item(string name, string type, int bonusPower)        //constructor
    : m_name(name), m_type(type), m_bonusPower(bonusPower){
}


string Item::getName() const{  //Returns item name
return m_name;
}


string Item::getType() const{  //returns item type
return m_type;
}


int Item::getBonusPower() const{  //returns how much strength item adds to the hero
return m_bonusPower;
}