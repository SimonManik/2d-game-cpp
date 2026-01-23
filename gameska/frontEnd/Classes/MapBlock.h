#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "MainInheriteClass.h" // Musi znat rodice
#include "../../backEnd/types/Vec2.h"

class Item; //na pozdej

class MapBlock : public MainInheriteClass {
private:
    bool isPassable; // True = podlaha, False = zed



public:
    // Konstruktor
    MapBlock(Vec2 pos, char symbol, Color color, bool startPassable);

    // Destruktor
    ~MapBlock() override;

    // Povinna metoda update (protoze rodic ji mel ciste virtualni)
    void update() override;

    // Getter
    bool getIsPassable() const { return isPassable; }


};

#endif //MAPBLOCK_H
