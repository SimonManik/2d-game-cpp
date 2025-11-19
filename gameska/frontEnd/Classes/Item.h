//
// Created by elisk on 19.11.2025.
//

#ifndef ZOO_ZS2025_2026_XJANOTA3_ITEM_H
#define ZOO_ZS2025_2026_XJANOTA3_ITEM_H
#include <string>

using namespace std;

class Item {
private:
    string m_name;    //Dagger, sword, bow etc.
    string m_type;   //Weapon, key, scroll,
    int m_bonusPower; // +1 dagger / +2 sword /+0key

public:
Item( string name, string type, int bonusPower);

string getName() const;
string getType() const;
int getBonusPower() const;

};


#endif //ZOO_ZS2025_2026_XJANOTA3_ITEM_H