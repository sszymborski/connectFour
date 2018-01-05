#include "Game.h"

#include <iostream>

Game::Game()
{
    gui = new Gui();
    board = new int* [WIDTH];
    for(int i = 0; i < WIDTH; ++i)
        board[i] = new int[HEIGHT];
    for(int i = 0; i < WIDTH; ++i)
        for(int j = 0; j < HEIGHT; ++j)
            board[i][j] = 0;
    whoPlay=1;
}

Game::~Game()
{
    delete gui;
    for(int i = 0; i < WIDTH; ++i)
        delete board[i];
    delete board;
}

void Game::start()
{
    AI *ai = new AI ();
    int colNumber;
    gui->show(board);
    while(1)
    {
        colNumber = gui->mouse();
        //dzieki temu if-owi obraz rysowany jest nie bez przerwy, ale tylko jak jest jakis input
        if(colNumber != -2) //kiedy zostal wcisniety klawisz myszki lub ESC
        {
            if(colNumber != -1)
            {
                if(board[colNumber][0] != 0) //jesli w kolumnie nie ma ju¿ miejsca na klocek
                    continue;
                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {

                        cout << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                        board[colNumber][j] = RED;
                        break;
                    }
                colNumber = ai -> doRandMove();
                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        cout << "Yellow on " << "\t" << colNumber << " " << j << endl;
                        board[colNumber][j] = YELLOW;
                        break;
                    }
            }
            gui->show(board);
            if(checkWin() || colNumber == -1)
            {
                cout << "END OF THE GAME" << endl;
                break;
            }
        }
    }
}

bool Game::checkWin()   // tests whether someone has won on the board at the moment
{
    int actual;
    for(int i = 0; i < WIDTH; ++i)   // tests 4 fields vertically to up
        for(int j = HEIGHT-1; j > HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i][j-1] && actual == board[i][j-2] && actual == board[i][j-3])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i << "x" << j-1 <<", "
                         << i << "x" << j-2 <<", "
                         << i << "x" << j-3 << "."
                         << endl;
                    return true;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields horizontally to right
        for(int j = 0; j < HEIGHT; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j] && actual == board[i+2][j] && actual == board[i+3][j])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i+1 << "x" << j <<", "
                         << i+2 << "x" << j <<", "
                         << i+3 << "x" << j << "."
                         << endl;
                    return true;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields across to up and right
        for(int j = HEIGHT-1; j >  HEIGHT-4; --j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j-1] && actual == board[i+2][j-2] && actual == board[i+3][j-3])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i+1 << "x" << j-1 <<", "
                         << i+2 << "x" << j-2 <<", "
                         << i+3 << "x" << j-3 << "."
                         << endl;
                    return true;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // tests 4 fields across to down and right
        for(int j = 0; j < HEIGHT-3; ++j)
            if(board[i][j] != 0)
            {
                actual = board[i][j];
                if(actual == board[i+1][j+1] && actual == board[i+2][j+2] && actual == board[i+3][j+3])
                {
                    cout << "Win by "
                         << i << "x" << j << ", "
                         << i+1 << "x" << j+1 <<", "
                         << i+2 << "x" << j+2 <<", "
                         << i+3 << "x" << j+3 << "."
                         << endl;
                    return true;
                }
            }
    return false;
}
