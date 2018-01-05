#include "Game.h"

#include <iostream>

Game::Game(int modeArg)
{
    mode = modeArg;
    whoPlays = 1;

    gui = new Gui();
    ai = new AI(5);
    board = new int* [WIDTH];

    for(int i = 0; i < WIDTH; ++i)
        board[i] = new int[HEIGHT];

    for(int i = 0; i < WIDTH; ++i)
        for(int j = 0; j < HEIGHT; ++j)
            board[i][j] = 0;
}

Game::~Game()
{
    delete gui;
    delete ai;

    for(int i = 0; i < WIDTH; ++i)
        delete board[i];

    delete board;
}

void Game::start()
{
    int colNumber;
    gui->display(board);
    while(1)
    {
        colNumber = gui->getInput();
        //dzieki temu if-owi obraz rysowany jest nie bez przerwy, ale tylko jak jest jakis input
        if(colNumber != -2) //kiedy zostal wcisniety klawisz myszki lub ESC
        {
            if(colNumber == -1) // jesli esc
            {
                cout << "END OF THE GAME" << endl;
                break;
            }
            if(mode == 1)       // gracz vs ai
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
                do
                {
                    colNumber = ai -> doRandMove();
                }
                while(board[colNumber][0] != 0);

                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        cout << "Yellow on " << "\t" << colNumber << " " << j << endl;
                        board[colNumber][j] = YELLOW;
                        break;
                    }
            }
            else if(mode == 2)
            {
                do
                {
                    colNumber = ai -> doRandMove();
                }
                while(board[colNumber][0] != 0);

                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        if(whoPlays)
                        {
                            cout << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                            board[colNumber][j] = RED;
                            whoPlays =! whoPlays;
                            break;
                        }
                        else
                        {
                            cout << "Yellow on " << "\t" << colNumber << " " << j << endl;
                            board[colNumber][j] = YELLOW;
                            whoPlays =! whoPlays;
                            break;
                        }
                    }
            }
        }
        gui->display(board);
        if(checkWin()) // jesli wygrana
        {
            cout << "END OF THE GAME" << endl;
            while(1)
            {
                if(gui->getInput() == -1)
                    break;
            }
            break;
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
