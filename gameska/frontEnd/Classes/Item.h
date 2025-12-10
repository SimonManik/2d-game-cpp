#ifndef ITEM_H
#define ITEM_H

#include <string>


class Item {
protected:
    std::string m_name;
    std::string m_type;
    int m_bonusPower;

public:
    // Parametric Constructor
    Item(const std::string& name, const std::string& type, int bonusPower);

    //  Destructor
    virtual ~Item();

    // Getters
    std::string getName() const;
    std::string getType() const;
    int getBonusPower() const;


    virtual std::string getDescription() const;
};

#endif // ITEM_H