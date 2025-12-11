#include "MapBlock.h"
#include "Item.h"

//mapblock resi jen sebe a nic jineho - napr jestli je cervena
//ci pruchozi atd. neresi jak je velka mapa atd


// Konstruktor
MapBlock::MapBlock(int startX, int startY, int startZ, char symbol, bool startPassable)
    // Volame konstruktor rodice a nastavujeme mu typ Wall (obecne blok)
    : MainInheriteClass(startX, startY, startZ, ObjectType::Wall, symbol),
      isPassable(startPassable),
      p_item(nullptr) //na zazacku je slot prazdny, nikam neukazuje
{
}

//destruktor

MapBlock::~MapBlock(){
    // Pokud tento blok drzi nejaky item, smaze se z pameti
    if (p_item != nullptr) {
        delete p_item;
        p_item = nullptr;
    }
}

// Setter pro polozeni itemu
void MapBlock::setItem(Item* newItem) {
    p_item = newItem;
}

// getter pro ziskani
Item* MapBlock::getItem() {
    return p_item;
}



// Update - zatim prazdny, bloky nic nedelaji
void MapBlock::update() {
    // Zde by byla logika, kdyby zdi treba blikaly
}

