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
    int column, maxValue = -100000;

    for(int k = 0; k < WIDTH; ++k)
        if(tab[k][0] == 0)
        {
            int tabCopy[WIDTH][HEIGHT];

            for(int i = 0; i < WIDTH; ++i)
                for(int j = 0; j < HEIGHT; ++j)
                    tabCopy[i][j] = tab[i][j];

            for(int j = HEIGHT-1; j >= 0; --j)
                if(tab[k][j] == 0)
                {
                    tab[k][j] = color;
                    break;
                }

            int value = alphabeta(tab, color, false, depth-1, -100000, 100000);
            if(value > maxValue)
            {
                maxValue = value;
                column = k;
            }

            for(int i = 0; i < WIDTH; ++i)
                for(int j = 0; j < HEIGHT; ++j)
                    tab[i][j] = tabCopy[i][j];
        }

    return column;
}

int AI::alphabeta(int** tab, int color, bool whoPlays, int howDeep, int alphaArg, int betaArg)
{
    if(howDeep == 0 || checkWin(tab))
        return evaluate(tab, color);

    int myColor = (color == RED ? RED : YELLOW);
    int oppColor = (color == RED ? YELLOW : RED);
    int alpha = alphaArg, beta = betaArg;
    int tabCopy[WIDTH][HEIGHT];

    if(!whoPlays) //jesli gra przeciwnik
    {
        for(int k = 0; k < WIDTH; ++k) //dla kazdego mozliwego ruchu
        {
            if(tab[k][0] == 0)
            {
                for(int i = 0; i < WIDTH; ++i) //tablica zapasowa
                    for(int j = 0; j < HEIGHT; ++j)
                        tabCopy[i][j] = tab[i][j];

                for(int j = HEIGHT-1; j >= 0; --j) //wstawienie krazka w pierwsze wolne miejsce w kolumnie
                    if(tab[k][j] == 0)
                    {
                        tab[k][j] = oppColor;
                        break;
                    }

                int betaResult = alphabeta(tab, myColor, whoPlays, howDeep-1, alpha, beta);
                beta = (beta < betaResult ? beta : betaResult);

//                if(alpha >= beta) //odcinanie galezi alpha (???) TODO!
//                    break;

                for(int i = 0; i < WIDTH; ++i) //przywracanie stanu tablicy sprzed ruchu
                    for(int j = 0; j < HEIGHT; ++j)
                        tab[i][j] = tabCopy[i][j];
            }//if
        }//for
        return beta;
    }
    else //jesli my gramy
    {
        for(int k = 0; k < WIDTH; ++k) //dla kazdego mozliwego ruchu
        {
            if(tab[k][0] == 0)
            {
                int tabCopy[WIDTH][HEIGHT];
                for(int i = 0; i < WIDTH; ++i)
                    for(int j = 0; j < HEIGHT; ++j)
                        tabCopy[i][j] = tab[i][j];

                for(int j = HEIGHT-1; j >= 0; --j)
                    if(tab[k][j] == 0)
                    {
                        tab[k][j] = myColor;
                        break;
                    }

                int alphaResult = alphabeta(tab, myColor, !whoPlays, howDeep-1, alpha, beta);
                alpha = (alpha > alphaResult ? alpha : alphaResult);

//                if(alpha >= beta) //odcinanie galezi beta (???) TODO!
//                    break;

                for(int i = 0; i < WIDTH; ++i)
                    for(int j = 0; j < HEIGHT; ++j)
                        tab[i][j] = tabCopy[i][j];
            }//if
        }//for
        return alpha;
    }
}

bool AI::checkWin(int** board)
{
    int actual;
    for(int i = 0; i < WIDTH; ++i)   // tests 4 fields vertically to up
        for(int j = HEIGHT-1; j > HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i][j-1] && actual == board[i][j-2] && actual == board[i][j-3])
                    return true;
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields horizontally to right
        for(int j = 0; j < HEIGHT; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j] && actual == board[i+2][j] && actual == board[i+3][j])
                    return true;
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields across to up and right
        for(int j = HEIGHT-1; j >  HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j-1] && actual == board[i+2][j-2] && actual == board[i+3][j-3])
                    return true;
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields across to down and right
        for(int j = 0; j < HEIGHT-3; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j+1] && actual == board[i+2][j+2] && actual == board[i+3][j+3])
                    return true;
            }
    return false;
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
                                value += (actColor == color ? VALUE4 : BADVALUE4); //4s vertical
                            else if(tab[i][j-3] == 0)
                                value += (actColor == color ? VALUE3 : BADVALUE3); //3s vertical
                        }
                        else if (tab[i][j-2] == 0 && tab[i][j-3] == 0)
                            value += (actColor == color ? VALUE2 : BADVALUE2); //2s vertical
                    }
                    else if(tab[i][j-1] == 0 && tab[i][j-2] == 0 && tab[i][j-3] == 0)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //1s vertical

                    if(tab[i+1][j-1] == actColor) //diagonal
                    {
                        if(tab[i+2][j-2] == actColor)
                        {
                            if(tab[i+3][j-3] == actColor)
                                value += (actColor == color ? VALUE4 : BADVALUE4); //4s diagonal
                            else if(tab[i+3][j-3] == 0)
                            {
                                if(i > 0 && j < HEIGHT-1)
                                {
                                    if(tab[i-1][j+1] == 0)
                                        value += 2*(actColor == color ? VALUE3 : BADVALUE3); //3s diagonal (double-sided)
                                }
                                else
                                    value += (actColor == color ? VALUE3 : BADVALUE3); //3s diagonal
                            }
                        }
                        else if(tab[i+2][j-2] == 0 && tab[i+3][j-3] == 0)
                        {
                            if(i > 0 && j < HEIGHT-1)
                            {
                                if(tab[i-1][j+1] == 0)
                                    value += 2*(actColor == color ? VALUE2 : BADVALUE2); //2s diagonal (double-sided)
                            }
                            else
                                value += (actColor == color ? VALUE2 : BADVALUE2); //2s diagonal
                        }
                    }
                    else if(tab[i+1][j-1] == 0 && tab[i+2][j-2] == 0 && tab[i+3][j-3] == 0)
                    {
                        if(i > 0 && j < HEIGHT-1)
                        {
                            if(tab[i-1][j+1] == 0)
                                value += 2*(actColor == color ? VALUE1 : BADVALUE1);  //1s diagonal (double-sided)
                        }
                        else
                            value += (actColor == color ? VALUE1 : BADVALUE1); //1s diagonal
                    }
                }

                if(tab[i+1][j] == actColor) //horizontal
                {
                    if(tab[i+2][j] == actColor)
                    {
                        if(tab[i+3][j] == actColor)
                            value += (actColor == color ? VALUE4 : BADVALUE4); //4s horizontal
                        else if(tab[i+3][j] == 0)
                        {
                            if(i > 0)
                            {
                                if(tab[i-1][j] == 0)
                                    value += 2*(actColor == color ? VALUE3 : BADVALUE3); //3s horizontal (double-sided)
                            }
                            else
                                value += (actColor == color ? VALUE3 : BADVALUE3); //3s horizontal
                        }
                    }
                    else if(tab[i+2][j] == 0 && tab[i+3][j] == 0)
                    {
                        if(i > 0)
                        {
                            if(tab[i-1][j] == 0)
                                value += 2*(actColor == color ? VALUE2 : BADVALUE2); //2s horizontal (double-sided)
                        }
                        else
                            value += (actColor == color ? VALUE2 : BADVALUE2); //2s horizontal
                    }
                }
                else if(tab[i+1][j] == 0 && tab[i+2][j] == 0 && tab[i+3][j] == 0)
                {
                    if(i > 0)
                    {
                        if(tab[i-1][j] == 0)
                            value += 2*(actColor == color ? VALUE1 : BADVALUE1); //1s horizontal (double-sided)
                    }
                    else
                        value += (actColor == color ? VALUE1 : BADVALUE1); //1s horizontal
                }
            }

            if(i > 2 && j > 2)
            {
                if(tab[i-1][j-1] == actColor) //reverse diagonal (up-left)
                {
                    if(tab[i-2][j-2] == actColor)
                    {
                        if(tab[i-3][j-3] == actColor)
                            value += (actColor == color ? VALUE4 : BADVALUE4); //4s reverse diagonal
                        else if(tab[i-3][j-3] == 0)
                        {
                            if(i < WIDTH-1 && j < HEIGHT-1)
                            {
                                if(tab[i+1][j+1] == 0)
                                    value += 2*(actColor == color ? VALUE3 : BADVALUE3); //3s reverse diagonal (double-sided)
                            }
                            else
                                value += (actColor == color ? VALUE3 : BADVALUE3); //3s reverse diagonal
                        }
                    }
                    else if(tab[i-2][j-2] == 0 && tab[i-3][j-3] == 0)
                    {
                        if(i < WIDTH-1 && j < HEIGHT-1)
                        {
                            if(tab[i+1][j+1] == 0)
                                value += 2*(actColor == color ? VALUE2 : BADVALUE2); //2s reverse diagonal (double-sided)
                        }
                        else
                            value += (actColor == color ? VALUE2 : BADVALUE2); //2s reverse diagonal
                    }
                }
                else if(tab[i-1][j-1] == 0 && tab[i-2][j-2] == 0 && tab[i-3][j-3] == 0)
                {
                    if(i < WIDTH-1 && j < HEIGHT-1)
                    {
                        if(tab[i+1][j+1] == 0)
                            value += 2*(actColor == color ? VALUE1 : BADVALUE1);  //1s reverse diagonal (double-sided)
                    }
                    else
                        value += (actColor == color ? VALUE1 : BADVALUE1); //1s reverse diagonal
                }
            }
        }//for

    return value;
}
