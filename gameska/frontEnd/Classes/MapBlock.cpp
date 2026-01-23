#include "MapBlock.h"

//mapblock resi jen sebe a nic jineho - napr jestli je cervena
//ci pruchozi atd. neresi jak je velka mapa atd


// Konstruktor
MapBlock::MapBlock(Vec2 pos, char symbol, Color color, bool startPassable)
    : MainInheriteClass(pos, symbol, color, ObjectType::Wall)
    , isPassable(symbol == 'O' ? true : startPassable)
     {}

//destruktor

MapBlock::~MapBlock(){
    // Pokud tento blok drzi nejaky item, smaze se z pameti

}




// Update - zatim prazdny, bloky nic nedelaji
void MapBlock::update() {
    // Zde by byla logika, kdyby zdi treba blikaly
}

