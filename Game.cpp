#include "Game.h"

#include <iostream>

Game::Game()
{
    whoPlays = 1;

    gui = new Gui();
    ai = new AI(7);
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
    mode = gui->showStartWindow();
    cout << "Tryb to " << mode << endl;
    fstream plik("log.txt", ios::out | ios::app);
    if(plik.good())
    {
        plik.seekp(0, ios_base::end);
        plik << "Tryb to " << mode << endl;
        plik.close();
    }
    int colNumber, aiNumber;
    int first = 1; // zmienna ktora odpowiada za mozliwosc ponownego ruchu gracza bez ruchu ai w momencie braku miejsca w kolumnie
    int freeBlocks = WIDTH*HEIGHT;

    if(mode == 2)
    {
        do
        {
            aiNumber = ai -> makeMove(board, YELLOW);
        }
        while(board[aiNumber][0] != 0);

        for(int j = HEIGHT-1; j >= 0; --j)
            if(board[aiNumber][j] == 0)
            {
                cout << "Yellow on " << "\t" << aiNumber << " " << j << endl;
                fstream plik("log.txt", ios::out | ios::app);
                if(plik.good())
                {
                    plik.seekp(0, ios_base::end);
                    plik << "Yellow on " << "\t" << aiNumber << " " << j << endl;
                    plik.close();
                }
                board[aiNumber][j] = YELLOW;
                --freeBlocks;
                break;
            }

    }

    if(mode!=-1)
        gui->display(board);


    while(mode!=-1)
    {
        colNumber = gui->getInput();
        //dzieki temu if-owi obraz rysowany jest nie bez przerwy, ale tylko jak jest jakis input
        if(colNumber != -2) //kiedy zostal wcisniety klawisz myszki lub ESC
        {
            if(colNumber == -1) // jesli esc
            {
                cout << "END OF THE GAME" << endl;
                fstream plik("log.txt", ios::out | ios::app);
                if(plik.good())
                {
                    plik.seekp(0, ios_base::end);
                    plik << "END OF THE GAME\n" << endl;
                    plik.close();
                }
                break;
            }
            if(mode == 1 || mode == 2)       // gracz vs ai lub ai vs gracz(wtedy ruch byl wczesniej juz)
            {
                if(board[colNumber][0] != 0) //jesli w kolumnie nie ma ju¿ miejsca na klocek
                    continue;
                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        cout << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                        fstream plik("log.txt", ios::out | ios::app);
                        if(plik.good())
                        {
                            plik.seekp(0, ios_base::end);
                            plik << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                            plik.close();
                        }
                        board[colNumber][j] = RED;
                        --freeBlocks;
                        break;
                    }
                gui -> display(board);

                if(checkWin() || freeBlocks == 0) // jesli wygrana
                {
                    if(freeBlocks == 0)
                    {
                        cout << "DRAW" << endl;
                        fstream plik("log.txt", ios::out | ios::app);
                        if(plik.good())
                        {
                            plik.seekp(0, ios_base::end);
                            plik << "DRAW\n" << endl;
                            plik.close();
                        }
                    }

                    cout << "END OF THE GAME" << endl;
                    fstream plik("log.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik << "END OF THE GAME\n" << endl;
                        plik.close();
                    }

                    while(1)
                    {
                        if(gui->getInput() == -1)
                            break;
                    }
                    break;
                }

                do
                {
                    colNumber = ai -> makeMove(board, YELLOW);
                }
                while(board[colNumber][0] != 0);

                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        cout << "Yellow on " << "\t" << colNumber << " " << j << endl;
                        fstream plik("log.txt", ios::out | ios::app);
                        if(plik.good())
                        {
                            plik.seekp(0, ios_base::end);
                            plik << "Yellow on " << "\t" << colNumber << " " << j << endl;
                            plik.close();
                        }

                        board[colNumber][j] = YELLOW;
                        --freeBlocks;
                        break;
                    }
            }
            else if (mode == 3)    // ai kontra ai
            {
                do
                {
                    if(whoPlays)
                        colNumber = ai -> makeMove(board, RED);
                    else
                        colNumber = ai -> makeMove(board, YELLOW);
                }
                while(board[colNumber][0] != 0);

                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        if(whoPlays)
                        {
                            cout << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                            fstream plik("log.txt", ios::out | ios::app);
                            if(plik.good())
                            {
                                plik.seekp(0, ios_base::end);
                                plik << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                                plik.close();
                            }
                            board[colNumber][j] = RED;
                            whoPlays = !whoPlays;
                            --freeBlocks;
                            break;
                        }
                        else
                        {
                            cout << "Yellow on " << "\t" << colNumber << " " << j << endl;
                            fstream plik("log.txt", ios::out | ios::app);
                            if(plik.good())
                            {
                                plik.seekp(0, ios_base::end);
                                plik << "Yellow on " << "\t" << colNumber << " " << j << endl;
                                plik.close();
                            }
                            board[colNumber][j] = YELLOW;
                            whoPlays = !whoPlays;
                            --freeBlocks;
                            break;
                        }
                    }
            }
            gui->display(board);
            if(checkWin() || freeBlocks == 0) // jesli wygrana
            {
                if(freeBlocks == 0)
                {
                    cout << "DRAW" << endl;
                    fstream plik("log.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik << "DRAW\n" << endl;
                        plik.close();
                    }
                }

                cout << "END OF THE GAME" << endl;
                fstream plik("log.txt", ios::out | ios::app);
                if(plik.good())
                {
                    plik.seekp(0, ios_base::end);
                    plik << "END OF THE GAME\n" << endl;
                    plik.close();
                }
                while(1)
                {
                    if(gui->getInput() == -1)
                        break;
                }
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
                    fstream plik("log.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik << "Win by "
                             << i << "x" << j << ", "
                             << i << "x" << j-1 <<", "
                             << i << "x" << j-2 <<", "
                             << i << "x" << j-3 << "."
                             << endl;
                        plik.close();
                    }
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
                    fstream plik("log.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik << "Win by "
                             << i << "x" << j << ", "
                             << i+1 << "x" << j <<", "
                             << i+2 << "x" << j <<", "
                             << i+3 << "x" << j << "."
                             << endl;
                        plik.close();
                    }
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
                    fstream plik("log.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik << "Win by "
                             << i << "x" << j << ", "
                             << i+1 << "x" << j-1 <<", "
                             << i+2 << "x" << j-2 <<", "
                             << i+3 << "x" << j-3 << "."
                             << endl;
                        plik.close();
                    }
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
                    fstream plik("log.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik << "Win by "
                             << i << "x" << j << ", "
                             << i+1 << "x" << j+1 <<", "
                             << i+2 << "x" << j+2 <<", "
                             << i+3 << "x" << j+3 << "."
                             << endl;
                        plik.close();
                    }
                    return true;
                }
            }
    return false;
}
