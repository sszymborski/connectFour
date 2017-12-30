#include "Gra.h"
#include <iostream>

Gra::Gra()
{
    gui = new Gui();
    tablicaDoGry = new int* [SZEROKOSC];

    for(int i = 0; i < SZEROKOSC; i++)
            tablicaDoGry[i] = new int[WYSOKOSC];

    for(int i = 0; i < SZEROKOSC; i++)
        for(int j = 0; j < WYSOKOSC; j++)
            tablicaDoGry[i][j] = 0;
}

Gra::~Gra()
{
    delete gui;

    for(int i = 0; i < SZEROKOSC; i++)
        delete tablicaDoGry[i];

    delete tablicaDoGry;
}

void Gra::graj()
{
    int inputCode;
    gui->wyswietl(tablicaDoGry);

    while(1)
    {
        inputCode = gui->myszka(tablicaDoGry);

        //dzieki temu if-owi obraz rysowany jest nie bez przerwy, ale tylko jak jest jakis input
        if(inputCode != 0) //kiedy zostal wcisniety klawisz myszki lub ESC
        {
            gui->wyswietl(tablicaDoGry);

            if(checkWin() || inputCode == -1)
            {
                std::cout << "KONIEC GRY" << std::endl;
                break;
            }
        }
    }
}

bool Gra::checkWin()   // tests whether someone has won on the board at the moment
{
    int actual;
    for(int i = 0; i < SZEROKOSC; ++i)   // tests 4 fields vertically to up
        for(int j = WYSOKOSC-1; j > WYSOKOSC-4; --j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i][j-1] && actual == tablicaDoGry[i][j-2] && actual == tablicaDoGry[i][j-3])
                {
                    std::cout << "Win by "
                    << i << "x" << j << ", "
                    << i << "x" << j-1 <<", "
                    << i << "x" << j-2 <<", "
                    << i << "x" << j-3 << "."
                    << std::endl;
                    return true;
                }
            }
    for(int i = 0; i < SZEROKOSC-3; ++i)   // tests 4 fields horizontally to right
        for(int j = 0; j < WYSOKOSC; ++j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i+1][j] && actual == tablicaDoGry[i+2][j] && actual == tablicaDoGry[i+3][j])
                {
                    std::cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j <<", "
                    << i+2 << "x" << j <<", "
                    << i+3 << "x" << j << "."
                    << std::endl;
                    return true;
                }
            }
    for(int i = 0; i < SZEROKOSC-3; ++i)   // tests 4 fields across to up and right
        for(int j = WYSOKOSC-1; j >  WYSOKOSC-4; --j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i+1][j-1] && actual == tablicaDoGry[i+2][j-2] && actual == tablicaDoGry[i+3][j-3])
                {
                    std::cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j-1 <<", "
                    << i+2 << "x" << j-2 <<", "
                    << i+3 << "x" << j-3 << "."
                    << std::endl;
                    return true;
                }
            }
    for(int i = 0; i < SZEROKOSC-3; ++i)   // tests 4 fields across to down and right
        for(int j = 0; j < WYSOKOSC-3; ++j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i+1][j+1] && actual == tablicaDoGry[i+2][j+2] && actual == tablicaDoGry[i+3][j+3])
                {
                    std::cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j+1 <<", "
                    << i+2 << "x" << j+2 <<", "
                    << i+3 << "x" << j+3 << "."
                    << std::endl;
                    return true;
                }
            }

    return false;
}
