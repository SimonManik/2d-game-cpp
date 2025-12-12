//
// Created by elisk on 12.12.2025.
//

#include "Key.h"

Key::Key(const std::string& name, int lockId)
    : Item(name, "Key", 0), m_lockId(lockId) {
}

int Key::getLockId() const {
    return m_lockId;
}

std::string Key::getDescription() const {
    return "A key with ID #" + std::to_string(m_lockId) + ". Used to open locked objects.";
}