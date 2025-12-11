
#include "Map.h"
#include <cstdlib> // nahodna cisla
#include <ctime>   // Pro funkci time() aby byla náhoda pokaždé jiná
#include "Item.h"

//map resi celek - jak je velka mistnost, kde jsou zdi ci dvere
// atd to je rozdil oproti jen map blocku

//  Initializer List pro nastaveni rozmeru
Map::Map(int w, int h) : width(w), height(h) {
    // Zatim je mrizka prazdna naplnime ji az zavolanim generateTestMap()
}

// Destruktor
Map::~Map() {
    // projdem vsechny radky (Y)
    for (int y = 0; y < gameMap.size(); ++y) {
        // projdem vsechny sloupce v radku (X)
        for (int x = 0; x < gameMap[y].size(); ++x) {
            // Smazeme konkretni objekt MapBlock z pameti
            delete gameMap[y][x];
        }
        // vycisteni radek pointeru, aby nezustaly viset
        gameMap[y].clear();
    }
    // Nakonec vycistime hlavni vektor radku
    gameMap.clear();
}

// Generovani testovaci mapy
void Map::generateTestMap() {

    // nahoda
    std::srand(std::time(0));

    // 1. Nastavime pocet radku (vysku)
    gameMap.resize(height);

    for (int y = 0; y < height; ++y) {
        // 2. Kazdy radek roztahneme na pozadovanou sirku
        gameMap[y].resize(width);

        for (int x = 0; x < width; ++x) {
            // 3. Logika pro urceni typu bloku
            
            // Pokud jsme na okraji mapy (prvni/posledni radek nebo sloupec) -> ZED
            bool isWall = (x == 0 || x == width - 1 || y == 0 || y == height - 1);

            MapBlock* newBlock = nullptr;

            if (isWall) {
                // Vytvorime ZED (#), ktera je nepruchozi (false)
                // Souradnice Z nastavime na 0
                newBlock = new MapBlock(x, y, 0, '#', false);
            } else {
                // Vytvorime PODLAHU (.), ktera je pruchozi (true)
                newBlock = new MapBlock(x, y, 0, '.', true);

                // Generovani itemu (jen pro podlahu)
                if (std::rand() % 100 < 10) {
                    //  nový item
                    Item* loot = new Item("Dagger", "Weapon", 2);
                    newBlock->setItem(loot);
                }
                // ---------------------------------------------------------------
            }

            // Ulozime pointer na novy blok do mrizky
            gameMap[y][x] = newBlock;
        }
    }
}

// Ziskani bloku na konkretnich souradnicich
MapBlock* Map::getBlockAt(int x, int y) {
    // Bezpecnostni kontrola: Jsme uvnitr mapy?
    // Pokud se zeptas na souradnice mimo pole, program by spadl, proto to hlidame.
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return gameMap[y][x];
    }
    
    // Pokud jsme mimo mapu, vratime nullptr (nic)
    return nullptr;
}



