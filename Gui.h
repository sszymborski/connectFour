#ifndef GUI_H
#define GUI_H

#include <allegro.h>
#include <cmath>
#include <cstdlib>

#define PUCK 100

using namespace std;

class Gui
{
    BITMAP * buffer;
    BITMAP * red;
    BITMAP * yellow;
    BITMAP * mode_1;
    BITMAP * mode_2;
    BITMAP * mode_3;
    int mx, my, mb;

public:
    Gui();
    ~Gui();
    void mouse();
    int showStartWindow();
    int getInput(); //-1 -> ESC; 1 -> LPM; 2 -> PPM; 0 - nic
    void display(int **tab); //funkcja wyswietlajaca bitmapy na ekran
};

#endif // GUI_H
