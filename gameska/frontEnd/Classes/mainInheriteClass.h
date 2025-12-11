using namespace std;

#ifndef MAININHERITECLASS_H
#define MAININHERITECLASS_H

#include <string>
#include "../../backEnd/types/Vec2.h"
#include "../../backEnd/types/Color.h"

// predelano od metodeje, myslel jsem to timhle zpusobem

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

    // x,y
    Vec2 m_position;
    // Znak pro vykresleni v konzoli (napr. '#', '@')
    char m_displayChar;
    // Typ objektu (vybrano z enumu vyse)
    ObjectType m_type;
    //barva charu
    Color m_color;

public:
    // Konstruktor: Nastavi zakladni hodnoty pri vytvoreni objektu.
    MainInheriteClass(Vec2 pos, char displayChar, Color color, ObjectType type)
        : m_position(pos)
        , m_displayChar(displayChar)
        , m_color(color)
        , m_type(type) {
    }

    // Virtualni destruktor:
    // Kriticky dulezite pro dedicnost. Zajisti, ze se spravne uvolni pamet i u potomku,
    // kdyz mazeme objekt pres pointer na rodice (MainInheriteClass*).
    virtual ~MainInheriteClass() = default;

    //  Gettery
    // 'const' nemeni stav objektu (je to jen cteni).
    Vec2 getPosition() const { return m_position; }
    char getDisplayChar() const { return m_displayChar; }
    Color getColor() const { return m_color; }
    string getColorAnsi() const { return ColorUtils::toAnsiCode(m_color); }
    ObjectType getType() const { return m_type; }

    //  setter
    void setPosition(Vec2 pos) { m_position = pos; }

    // --- Virtualni metody ---

    // Ciste virtualni metoda (Pure Virtual Method).
    // '= 0' znamena, ze tato trida nema implementaci.
    // Kazda trida, ktera z teto dedi (Enemy, MapBlock), MUSI tuto metodu naprogramovat.
    // Diky tomu je tato trida ABSTRAKTNI (nejde vytvorit jen tak sama o sobe).
    virtual void update() = 0;
};

#endif //MAININHERITECLASS_H