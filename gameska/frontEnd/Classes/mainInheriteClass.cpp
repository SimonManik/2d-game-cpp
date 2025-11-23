
//  Propojeni s hlavickou
#include "mainInheriteClass.h"

// Implementace konstruktoru
MainInheriteClass::MainInheriteClass(int startX, int startY, int startZ, ObjectType startType, char startSymbol)
    : x(startX), y(startY), z(startZ), type(startType), symbol(startSymbol) // <- Initializer List
{   //ta dvojtecka na 7 radku je "most" co dostanu zvenku a co nastavim uvnitr tzv zacatek inicializatoru konstruktoru
    // 4. Prazdne telo
}

//  Implementace metody setPosition
void MainInheriteClass::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}