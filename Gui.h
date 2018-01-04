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
    int mx, my, mb;
    bool whoPlay; //doPVP

public:
    Gui();
    ~Gui();
    int mouse(int **tab); //-1 -> ESC; 1 -> LPM; 2 -> PPM; 0 - nic
    void show(int **tab); //funkcja wyswietlajaca bitmapy na ekran
};

#endif // GUI_H
