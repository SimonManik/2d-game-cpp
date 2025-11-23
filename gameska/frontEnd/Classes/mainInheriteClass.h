

#ifndef MAININHERITECLASS_H
#define MAININHERITECLASS_H

// Enum pro urceni typu objektu.
// Pouzivame 'enum class', aby se nazvy (Player, Enemy) nepletly s jinymi promennymi v kodu.
enum class ObjectType {
    Player,     // Hrac
    Enemy,      // Nepritel
    Wall,       // Zed
    Item,       // Predmet
    Undefined   // Nedefinovano
};

class MainInheriteClass {
protected:
    // Sekce 'protected': Tyto promenne vidi tato trida A VSECHNY tridy, ktere z ni dedi (potomci).
    // To umoznuje tridam jako Enemy nebo MapBlock primo menit svou pozici.

    int x;              // Souradnice X (vodorovne)
    int y;              // Souradnice Y (svisle)
    int z;              // Vrstva (hloubka vykreslovani) - podle zadani
    ObjectType type;    // Typ objektu (vybrano z enumu vyse)
    char symbol;        // Znak pro vykresleni v konzoli (napr. '#', '@')

public:
    // Konstruktor: Nastavi zakladni hodnoty pri vytvoreni objektu.
    MainInheriteClass(int startX, int startY, int startZ, ObjectType startType, char startSymbol);

    // Virtualni destruktor:
    // Kriticky dulezite pro dedicnost. Zajisti, ze se spravne uvolni pamet i u potomku,
    // kdyz mazeme objekt pres pointer na rodice (MainInheriteClass*).
    virtual ~MainInheriteClass() = default;

    //  Gettery
    // 'const' nemeni stav objektu (je to jen cteni).
    int getX() const { return x; }
    int getY() const { return y; }
    int getZ() const { return z; }
    char getSymbol() const { return symbol; }
    ObjectType getType() const { return type; }

    //  setter
    void setPosition(int newX, int newY);

    // --- Virtualni metody ---

    // Ciste virtualni metoda (Pure Virtual Method).
    // '= 0' znamena, ze tato trida nema implementaci.
    // Kazda trida, ktera z teto dedi (Enemy, MapBlock), MUSI tuto metodu naprogramovat.
    // Diky tomu je tato trida ABSTRAKTNI (nejde vytvorit jen tak sama o sobe).
    virtual void update() = 0;
};

#endif //MAININHERITECLASS_H