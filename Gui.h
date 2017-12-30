#ifndef GUI_H
#define GUI_H

#include <allegro.h>
#include <cmath>
#include <cstdlib>

#define KRATKA 100

class Gui
{
    BITMAP * bufor;
    BITMAP * czerwony;
    BITMAP * zolty;
    int mx, my, mb;

    public:
        Gui();
        ~Gui();
        int myszka(int **tab); //-1 -> ESC; 1 -> LPM; 2 -> PPM; 0 - nic
        void wyswietl(int **tab); //funkcja wyswietlajaca bitmapy na ekran
};

#endif // GUI_H
