#ifndef AI_H
#define AI_H

#include <iostream>
#include <cstdlib>
#include <ctime>

#define INF 10000000

#define VALUE4 1000
#define VALUE3 100
#define VALUE2 10
#define VALUE1 1
#define BADVALUE4 -10000
#define BADVALUE3 -1000
#define BADVALUE2 -10
#define BADVALUE1 -1

using namespace std;

class AI
{
    int depth; //glebokosc drzewa

public:
    AI(int depthArg);
    ~AI();

    int makeMove(int** tab, int color); //funkcja wywolywana przez game

private:
    long long int evaluate(int** tab, int color); //funkcja obliczajaca wartosc sytuacji przedstawionej w tablicy tab, w jakiej znajduje sie gracz o kolorze color
    long long int alphabeta(int** tab, int color, bool whoPlays, int howDeep, int alphaArg, int betaArg); //rekurencyjny algorytm min-max z obcinaniem alfa-beta
    int checkWin(int** board);
    bool isFreeSpace(int** tab); //czy jest jeszcze wolne miejsce w ktorejs kolumnie
};

#endif // AI_H
