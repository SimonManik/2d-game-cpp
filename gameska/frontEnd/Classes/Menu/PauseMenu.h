#ifndef PAUSEMENU_H
#define PAUSEMENU_H

class PauseMenu {
public:
    enum Action { RESUME, EXIT_TO_MENU };

    static Action show();

private:
    static void draw(int selectedOption);
};

#endif