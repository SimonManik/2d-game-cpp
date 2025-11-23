#ifndef MAP_H
#define MAP_H

#include <vector>
#include "MapBlock.h"

class Map {
private:
    // 2D mrizka (vektor vektoru), ktera drzi ukazatele na jednotlive bloky mapy
    // ukazatel (*), protoze MapBlock je dcerina trida a chceme vyuzivat polymorfismus
    std::vector<std::vector<MapBlock*>> gameMap;

    int width;  // Sirka mapy (pocet sloupcu)
    int height; // Vyska mapy (pocet radku)

public:
    // Konstruktor Nastavi rozmery mapy
    Map(int w, int h);

    // Destruktor smazani pointeru
    ~Map();

    // Metoda pro vygenerovani testovaci urovne (zdi dokola, podlaha uvnitr)
    void generateTestMap();

    // Metoda pro ziskani konkretniho bloku na souradnicich X Y
    // Vraci pointer na blok
    MapBlock* getBlockAt(int x, int y);

    // Gettery pro rozmery mapy
    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif //MAP_H