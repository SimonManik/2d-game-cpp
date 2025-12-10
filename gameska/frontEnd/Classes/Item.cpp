#include "Item.h"

// Constructor
Item::Item(const std::string& name, const std::string& type, int bonusPower)
    : m_name(name), m_type(type), m_bonusPower(bonusPower) {
}

// Destructor
Item::~Item() {
    //to do
}

std::string Item::getName() const {
    return m_name;
}

std::string Item::getType() const {
    return m_type;
}

int Item::getBonusPower() const {
    return m_bonusPower;
}

std::string Item::getDescription() const {
    return "A generic item.";
}