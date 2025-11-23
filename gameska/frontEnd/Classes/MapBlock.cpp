#include "MapBlock.h"

//mapblock resi jen sebe a nic jineho - napr jestli je cervena
//ci pruchozi atd. neresi jak je velka mapa atd


// Konstruktor
MapBlock::MapBlock(int startX, int startY, int startZ, char symbol, bool startPassable)
    // Volame konstruktor rodice a nastavujeme mu typ Wall (obecne blok)
    : MainInheriteClass(startX, startY, startZ, ObjectType::Wall, symbol),
      isPassable(startPassable) 
{
}

// Update - zatim prazdny, bloky nic nedelaji
void MapBlock::update() {
    // Zde by byla logika, kdyby zdi treba blikaly
}