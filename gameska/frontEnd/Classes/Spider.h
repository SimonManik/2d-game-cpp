//
// Created by elisk on 25.11.2025.
//

#ifndef GAMESKA_SPIDER_H
#define GAMESKA_SPIDER_H

#include "Enemy.h"

class Spider: public Enemy{

public:
Spider() : Enemy ("Spider", 15, true, 35){
}

Spider(const int m_strength, const int m_health);

~Spider() override{}

void attack() const override;
};

#endif //GAMESKA_SPIDER_H