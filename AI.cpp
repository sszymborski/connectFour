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
    int column;
    long long int maxValue = -100000;

    cout << "\tkolumna:\t0\t1\t2\t3\t4\t5\t6" << endl;
    cout << "\tvalue:\t\t";

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

            long long int value = alphabeta(tab, color, false, depth-1, -1000000, 1000000);
            if(value > maxValue)
            {
                maxValue = value;
                column = k;
            }
            cout << value << "\t";

            for(int i = 0; i < WIDTH; ++i)
                for(int j = 0; j < HEIGHT; ++j)
                    tab[i][j] = tabCopy[i][j];
        }
        else
            cout << "--\t";
    cout << endl;

    return column;
}

long long int AI::alphabeta(int** tab, int color, bool whoPlays, int howDeep, int alphaArg, int betaArg)
{
    if(howDeep == 0)
        return evaluate(tab, color);

    int myColor = (color == RED ? RED : YELLOW);
    int oppColor = (color == RED ? YELLOW : RED);

    int winColor = checkWin(tab);
    if(winColor == oppColor && howDeep >= depth-3)
        return evaluate(tab, color) + 10*(BADVALUE4);
    else if(winColor == oppColor)
        return evaluate(tab, color) + howDeep*(BADVALUE4);
    else if(winColor == color && howDeep >= depth-3)
        return evaluate(tab, color) + 100*howDeep*VALUE4;
    else if(winColor == color)
        return evaluate(tab, color) + howDeep*VALUE4;

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

                if(alpha >= beta) //odcinanie galezi
                {
                    for(int i = 0; i < WIDTH; ++i) //przywracanie stanu tablicy sprzed ruchu
                        for(int j = 0; j < HEIGHT; ++j)
                            tab[i][j] = tabCopy[i][j];
                    break;
                }

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

                if(alpha >= beta) //odcinanie galezi
                {
                    for(int i = 0; i < WIDTH; ++i)
                        for(int j = 0; j < HEIGHT; ++j)
                            tab[i][j] = tabCopy[i][j];
                    break;
                }

                for(int i = 0; i < WIDTH; ++i)
                    for(int j = 0; j < HEIGHT; ++j)
                        tab[i][j] = tabCopy[i][j];
            }//if
        }//for
        return alpha;
    }//else
}

long long int AI::evaluate(int** tab, int color)
{
    long long int value = 0;

    for(int i = 0; i < WIDTH; ++i)
        for(int j = HEIGHT-1; j >= 0; --j)
        {
            if(tab[i][j] == 0)
                break;

            int actColor = tab[i][j];
            int oppColor = (actColor == RED ? YELLOW : RED);


            if(i < WIDTH-3) //4right
            {
                if(tab[i+1][j] == actColor && tab[i+2][j] == actColor && tab[i+3][j] == actColor)
                    value += (actColor == color ? VALUE4 : BADVALUE4); //4s right
                else if(tab[i+1][j] == actColor && tab[i+2][j] == actColor && tab[i+3][j] == 0)
                    value += (actColor == color ? VALUE3 : BADVALUE3); //3s right
                else if(tab[i+1][j] == actColor && tab[i+2][j] == 0 && tab[i+3][j] != oppColor)
                    value += (actColor == color ? VALUE2 : BADVALUE2); //2s right
                else if(tab[i+1][j] == 0 && tab[i+2][j] != oppColor && tab[i+3][j] != oppColor)
                    value += (actColor == color ? VALUE1 : BADVALUE1); //1s right

                if(j > 2) //4up-right
                {
                    if(tab[i+1][j-1] == actColor && tab[i+2][j-2] == actColor && tab[i+3][j-3] == actColor)
                        value += (actColor == color ? VALUE4 : BADVALUE4); //4s up-right
                    else if(tab[i+1][j-1] == actColor && tab[i+2][j-2] == actColor && tab[i+3][j-3] == 0)
                        value += (actColor == color ? VALUE3 : BADVALUE3); //3s up-right
                    else if(tab[i+1][j-1] == actColor && tab[i+2][j-2] == 0 && tab[i+3][j-3] != oppColor)
                        value += (actColor == color ? VALUE2 : BADVALUE2); //2s up-right
                    else if(tab[i+1][j-1] == 0 && tab[i+2][j-2] != oppColor && tab[i+3][j-3] != oppColor)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //1s up-right
                }

                if(j < HEIGHT-3) //up-left 0-0-0-x
                {
                    if(tab[i+3][j+3] != oppColor && tab[i+2][j+2] != oppColor && tab[i+1][j+1] == 0)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //0-0-0-x
                }
            }

            if(i < WIDTH-2 && i > 0) //horizontal 0-x-?-?
            {
                if(tab[i-1][j] == 0 && tab[i+1][j] == actColor && tab[i+2][j] == actColor)
                    value += (actColor == color ? VALUE3 : BADVALUE3); //0-x-1-1
                else if(tab[i-1][j] == 0 && tab[i+1][j] == actColor && tab[i+2][j] == 0)
                    value += (actColor == color ? VALUE2 : BADVALUE2); //0-x-1-0
                else if(tab[i-1][j] == 0 && tab[i+1][j] == 0 && tab[i+2][j] != oppColor)
                    value += (actColor == color ? VALUE1 : BADVALUE1); //0-x-0-0

                if(j > 1 && j < HEIGHT-1) //up-right 0-x-?-?
                {
                    if(tab[i-1][j+1] == 0 && tab[i+1][j-1] == actColor && tab[i+2][j-2] == actColor)
                        value += (actColor == color ? VALUE3 : BADVALUE3); //0-x-1-1
                    else if(tab[i-1][j+1] == 0 && tab[i+1][j-1] == actColor && tab[i+2][j-2] == 0)
                        value += (actColor == color ? VALUE2 : BADVALUE2); //0-x-1-0
                    else if(tab[i-1][j+1] == 0 && tab[i+1][j-1] == 0 && tab[i+2][j-2] != oppColor)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //0-x-0-0
                }

                if(j > 0 && j < HEIGHT-2) //up-left 0-0-x-?
                {
                    if(tab[i+2][j+2] != oppColor && tab[i+1][j+1] == 0 && tab[i-1][j-1] == actColor)
                        value += (actColor == color ? VALUE2 : BADVALUE2); //0-0-x-1
                    else if(tab[i+2][j+2] != oppColor && tab[i+1][j+1] == 0 && tab[i-1][j-1] == 0)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //0-0-x-0
                }
            }

            if(i < WIDTH-1 && i > 1) //horizontal 0-0-x-?
            {
                if(tab[i-2][j] != oppColor && tab[i-1][j] == 0 && tab[i+1][j] == actColor)
                    value += (actColor == color ? VALUE2 : BADVALUE2); //0-0-x-1
                else if(tab[i-2][j] != oppColor && tab[i-1][j] == 0 && tab[i+1][j] == 0)
                    value += (actColor == color ? VALUE1 : BADVALUE1); //0-0-x-0

                if(j > 0 && j < HEIGHT-2) //up-right 0-0-x-?
                {
                    if(tab[i-2][j+2] != oppColor && tab[i-1][j+1] == 0 && tab[i+1][j-1] == actColor)
                        value += (actColor == color ? VALUE2 : BADVALUE2); //0-0-x-1
                    else if(tab[i-2][j+2] != oppColor && tab[i-1][j+1] == 0 && tab[i+1][j-1] == 0)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //0-0-x-0
                }

                if(j > 1 && j < HEIGHT-1) //up-left 0-x-?-?
                {
                    if(tab[i+1][j+1] == 0 && tab[i-1][j-1] == actColor && tab[i-2][j-2] == actColor)
                        value += (actColor == color ? VALUE3 : BADVALUE3); //0-x-1-1
                    else if(tab[i+1][j+1] == 0 && tab[i-1][j-1] == actColor && tab[i-2][j-2] == 0)
                        value += (actColor == color ? VALUE2 : BADVALUE2); //0-x-1-0
                    else if(tab[i+1][j+1] == 0 && tab[i-1][j-1] == 0 && tab[i-2][j-2] != oppColor)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //0-x-0-0
                }
            }

            if(i > 2) //horizontal 0-0-0-x
            {
                if(tab[i-3][j] != oppColor && tab[i-2][j] != oppColor && tab[i-1][j] == 0)
                    value += (actColor == color ? VALUE1 : BADVALUE1); //0-0-0-x

                if(j < HEIGHT-3) //up-right 0-0-0-x
                {
                    if(tab[i-3][j+3] != oppColor && tab[i-2][j+2] != oppColor && tab[i-1][j+1] == 0)
                        value += (actColor == color ? VALUE1 : BADVALUE1);
                }

                if(j > 2) //up-left x-?-?-?
                {
                    if(tab[i-1][j-1] == actColor && tab[i-2][j-2] == actColor && tab[i-3][j-3] == actColor)
                        value += (actColor == color ? VALUE4 : BADVALUE4); //x-1-1-1
                    else if(tab[i-1][j-1] == actColor && tab[i-2][j-2] == actColor && tab[i-3][j-3] == 0)
                        value += (actColor == color ? VALUE3 : BADVALUE3); //x-1-1-0
                    else if(tab[i-1][j-1] == actColor && tab[i-2][j-2] == 0 && tab[i-3][j-3] != oppColor)
                        value += (actColor == color ? VALUE2 : BADVALUE2); //x-1-0-0
                    else if(tab[i-1][j-1] == 0 && tab[i-2][j-2] != oppColor && tab[i-3][j-3] != oppColor)
                        value += (actColor == color ? VALUE1 : BADVALUE1); //x-0-0-0
                }
            }

            if(j > 2)
            {
                if(tab[i][j-1] == 0)
                    value += (actColor == color ? VALUE1 : BADVALUE1); //1s up
                else if(tab[i][j-1] == actColor && tab[i][j-2] == 0)
                    value += (actColor == color ? VALUE2 : BADVALUE2); //2s up
                else if(tab[i][j-1] == actColor && tab[i][j-2] == actColor && tab[i][j-3] == 0)
                    value += (actColor == color ? VALUE3 : BADVALUE3); //3s up
                else if(tab[i][j-1] == actColor && tab[i][j-2] == actColor && tab[i][j-3] == actColor)
                    value += (actColor == color ? VALUE4 : BADVALUE4); //4s up
            }

        }//for

    return value;
}

int AI::checkWin(int** board)
{
    int actual;
    for(int i = 0; i < WIDTH; ++i)   // tests 4 fields vertically to up
        for(int j = HEIGHT-1; j > HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i][j-1] && actual == board[i][j-2] && actual == board[i][j-3])
                {
                    if(actual == RED)
                        return RED;
                    else
                        return YELLOW;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields horizontally to right
        for(int j = 0; j < HEIGHT; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j] && actual == board[i+2][j] && actual == board[i+3][j])
                {
                    if(actual == RED)
                        return RED;
                    else
                        return YELLOW;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields across to up and right
        for(int j = HEIGHT-1; j >  HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j-1] && actual == board[i+2][j-2] && actual == board[i+3][j-3])
                {
                    if(actual == RED)
                        return RED;
                    else
                        return YELLOW;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields across to down and right
        for(int j = 0; j < HEIGHT-3; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j+1] && actual == board[i+2][j+2] && actual == board[i+3][j+3])
                {
                    if(actual == RED)
                        return RED;
                    else
                        return YELLOW;
                }
            }
    return 0;
}
