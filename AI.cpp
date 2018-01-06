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

    for(int i = 0; i < WIDTH; ++i)
        for(int j = HEIGHT-1; j > 0; --j)
        {
            if(tab[i][j] == 0)
                continue;

            int actColor = tab[i][j];

            if(i < WIDTH-3)
            {
                if(j > 2)
                {
                    if(tab[i][j-1] == actColor) //vertical
                    {
                        if(tab[i][j-2] == actColor)
                        {
                            if(tab[i][j-3] == actColor)
                                value += (actColor == color ? VALUE4 : -VALUE4); //4s vertical
                            else if(tab[i][j-3] == 0)
                                value += (actColor == color ? VALUE3 : -VALUE3); //3s vertical
                        }
                        else if (tab[i][j-2] == 0 && tab[i][j-3] == 0)
                            value += (actColor == color ? VALUE2 : -VALUE2); //2s vertical
                    }
                    else if(tab[i][j-1] == 0 && tab[i][j-2] == 0 && tab[i][j-3] == 0)
                        value += (actColor == color ? VALUE1 : -VALUE1); //1s vertical

                    if(tab[i+1][j-1] == actColor) //diagonal
                    {
                        if(tab[i+2][j-2] == actColor)
                        {
                            if(tab[i+3][j-3] == actColor)
                                value += (actColor == color ? VALUE4 : -VALUE4); //4s diagonal
                            else if(tab[i+3][j-3] == 0)
                            {
                                if(i > 0 && j < HEIGHT-1)
                                {
                                    if(tab[i-1][j+1] == 0)
                                        value += 2*(actColor == color ? VALUE3 : -VALUE3); //3s diagonal (double-sided)
                                }
                                else
                                    value += (actColor == color ? VALUE3 : -VALUE3); //3s diagonal
                            }
                        }
                        else if(tab[i+2][j-2] == 0 && tab[i+3][j-3] == 0)
                        {
                            if(i > 0 && j < HEIGHT-1)
                            {
                                if(tab[i-1][j+1] == 0)
                                    value += 2*(actColor == color ? VALUE2 : -VALUE2); //2s diagonal (double-sided)
                            }
                            else
                                value += (actColor == color ? VALUE2 : -VALUE2); //2s diagonal
                        }
                    }
                    else if(tab[i+1][j-1] == 0 && tab[i+2][j-2] == 0 && tab[i+3][j-3] == 0)
                    {
                        if(i > 0 && j < HEIGHT-1)
                        {
                            if(tab[i-1][j+1] == 0)
                                value += 2*(actColor == color ? VALUE1 : -VALUE1);  //1s diagonal (double-sided)
                        }
                        else
                            value += (actColor == color ? VALUE1 : -VALUE1); //1s diagonal
                    }
                }

                if(tab[i+1][j] == actColor) //horizontal
                {
                    if(tab[i+2][j] == actColor)
                    {
                        if(tab[i+3][j] == actColor)
                            value += (actColor == color ? VALUE4 : -VALUE4); //4s horizontal
                        else if(tab[i+3][j] == 0)
                        {
                            if(i > 0)
                            {
                                if(tab[i-1][j] == 0)
                                    value += 2*(actColor == color ? VALUE3 : -VALUE3); //3s horizontal (double-sided)
                            }
                            else
                                value += (actColor == color ? VALUE3 : -VALUE3); //3s horizontal
                        }
                    }
                    else if(tab[i+2][j] == 0 && tab[i+3][j] == 0)
                    {
                        if(i > 0)
                        {
                            if(tab[i-1][j] == 0)
                                value += 2*(actColor == color ? VALUE2 : -VALUE2); //2s horizontal (double-sided)
                        }
                        else
                            value += (actColor == color ? VALUE2 : -VALUE2); //2s horizontal
                    }
                }
                else if(tab[i+1][j] == 0 && tab[i+2][j] == 0 && tab[i+3][j] == 0)
                {
                    if(i > 0)
                    {
                        if(tab[i-1][j] == 0)
                            value += 2*(actColor == color ? VALUE1 : -VALUE1); //1s horizontal (double-sided)
                    }
                    else
                        value += (actColor == color ? VALUE1 : -VALUE1); //1s horizontal
                }
            }

            if(i > 2 && j > 2)
            {
                if(tab[i-1][j-1] == actColor) //reverse diagonal
                {
                    if(tab[i-2][j-2] == actColor)
                    {
                        if(tab[i-3][j-3] == actColor)
                            value += (actColor == color ? VALUE4 : -VALUE4); //4s reverse diagonal
                        else if(tab[i-3][j-3] == 0)
                        {
                            if(i < WIDTH-1 && j < HEIGHT-1)
                            {
                                if(tab[i+1][j+1] == 0)
                                    value += 2*(actColor == color ? VALUE3 : -VALUE3); //3s reverse diagonal (double-sided)
                            }
                            else
                                value += (actColor == color ? VALUE3 : -VALUE3); //3s reverse diagonal
                        }
                    }
                    else if(tab[i-2][j-2] == 0 && tab[i-3][j-3] == 0)
                    {
                        if(i < WIDTH-1 && j < HEIGHT-1)
                        {
                            if(tab[i+1][j+1] == 0)
                                value += 2*(actColor == color ? VALUE2 : -VALUE2); //2s reverse diagonal (double-sided)
                        }
                        else
                            value += (actColor == color ? VALUE2 : -VALUE2); //2s reverse diagonal
                    }
                }
                else if(tab[i-1][j-1] == 0 && tab[i-2][j-2] == 0 && tab[i-3][j-3] == 0)
                {
                    if(i < WIDTH-1 && j < HEIGHT-1)
                    {
                        if(tab[i+1][j+1] == 0)
                            value += 2*(actColor == color ? VALUE1 : -VALUE1);  //1s reverse diagonal (double-sided)
                    }
                    else
                        value += (actColor == color ? VALUE1 : -VALUE1); //1s reverse diagonal
                }
            }
        }//for

    return value;
}
