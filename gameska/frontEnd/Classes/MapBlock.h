#ifndef MAPBLOCK_H
#define MAPBLOCK_H

#include "mainInheriteClass.h" // Musi znat rodice

class MapBlock : public MainInheriteClass {
private:
    bool isPassable; // True = podlaha, False = zed

public:
    // Konstruktor
    MapBlock(int startX, int startY, int startZ, char symbol, bool startPassable);

    // Destruktor
    ~MapBlock() override = default;

    // Povinna metoda update (protoze rodic ji mel ciste virtualni)
    void update() override;

    // Getter
    bool getIsPassable() const { return isPassable; }
};

#endif //MAPBLOCK_H