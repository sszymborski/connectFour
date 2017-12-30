#ifndef GRA_H
#define GRA_H

#include "Gui.h"

#define SZEROKOSC 7
#define WYSOKOSC 6
#define RED 1
#define YELLOW -1

class Gra
{
    int tryb; //rozroznia tryb gracz vs AI oraz AI vs AI
    int **tablicaDoGry;
    Gui *gui;

    public:
        Gra();
        ~Gra();
        void graj();
        bool checkWin();
};

#endif // GRA_H
