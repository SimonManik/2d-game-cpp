//
// Created by elisk on 12.12.2025.
//

#ifndef GAMESKA_KEY_H
#define GAMESKA_KEY_H
#include "Item.h"

class Key : public Item {
private:
    int m_lockId; //has to match ID of door/chest

public:
    Key(const std::string& name, int lockId);

    int getLockId() const;

    std::string getDescription() const override;
};


#endif //GAMESKA_KEY_H