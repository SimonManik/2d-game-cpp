#include "MapBlock.h"
#include "Item.h"

//mapblock resi jen sebe a nic jineho - napr jestli je cervena
//ci pruchozi atd. neresi jak je velka mapa atd


// Konstruktor
MapBlock::MapBlock(Vec2 pos, char symbol, Color color, bool startPassable)
    : MainInheriteClass(pos, symbol, color, ObjectType::Wall)
    , isPassable(startPassable)
    , p_item(nullptr) {
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

