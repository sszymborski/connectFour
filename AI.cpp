#include "Game.h"
#include "AI.h"

AI::AI(int depthArg)
{
    cout << "hej, tu AI" << endl;
    srand( time( NULL ) );
    depth = depthArg;
}

AI::~AI()
{
    //dtor
}

int AI::doRandMove()
{
    int number = rand();
    cout << "Wylosowano: " << number << endl;

    int goodNumber = number%7;
    cout << "Pionek na: " << goodNumber << endl;

    return goodNumber;
}

int AI::makeMove(int** tab, int color)
{
    return 0;
}

int AI::evaluate(int** tab, int color)
{
    int value = 0;
    int myColor = (color == RED ? RED : YELLOW);
    int oppColor = (color == RED ? YELLOW : RED);

    for(int i = 0; i < WIDTH; ++i)
        for(int j = HEIGHT-1; j > 0; --j)
        {
            if(tab[i][j] == 0)
                continue;

            int actColor = tab[i][j];

            if(j > 2)
            {
                if(tab[i][j-1] == actColor && tab[i][j-2] == actColor && tab[i][j-3] == actColor) //4s vertical
                    value += (actColor == color ? COUNT4 : -COUNT4);
                if(i < WIDTH-3);
            }

            if(i < WIDTH-3 && j > 2)
            {
                //if
            }
        }

    return value;
}
