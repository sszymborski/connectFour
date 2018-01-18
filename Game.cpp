#include "Game.h"

#include <iostream>

Game::Game(int depth1, int depth2)
{

    potrzebnyCzerwony = depth1;
    potrzebnyZolty = depth2;

    ruchyCzerwonego = 0;
    ruchyZoltego = 0;

    whoPlays = 1;

    gui = new Gui();
    ai1 = new AI(depth1);
    ai2 = new AI(depth2);
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
    delete ai1;
    delete ai2;
    for(int i = 0; i < WIDTH; ++i)
        delete board[i];
    delete board;
}

void Game::start()
{
   // mode = gui->showStartWindow();
    cout << "Tryb to " << mode << endl;

    mode = AIvsAI;
    auto time1 = std::chrono::nanoseconds::zero();
    auto time2 = std::chrono::nanoseconds::zero();

    int colNumber, aiNumber;
    int first = 1; // zmienna ktora odpowiada za mozliwosc ponownego ruchu gracza bez ruchu ai w momencie braku miejsca w kolumnie
    int freeBlocks = WIDTH*HEIGHT;

    if(mode == AIvsP)
    {
        do
        {
            aiNumber = ai1 -> makeMove(board, YELLOW);
        }
        while(board[aiNumber][0] != 0);

        for(int j = HEIGHT-1; j >= 0; --j)
            if(board[aiNumber][j] == 0)
            {
                cout << "Yellow on " << "\t" << aiNumber << " " << j << endl;
                board[aiNumber][j] = YELLOW;
                --freeBlocks;
                break;
            }

    }

    if(mode != -1)
        gui->display(board);


    while(mode != -1)
    {
        colNumber = gui->getInput();
        //dzieki temu if-owi obraz rysowany jest nie bez przerwy, ale tylko jak jest jakis input
        if(1)//colNumber != -2) //kiedy zostal wcisniety klawisz myszki lub ESC
        {
            if(colNumber == -1) // jesli esc
            {
                cout << "END OF THE GAME" << endl;
                break;
            }
            if(mode == PvsAI || mode == AIvsP)       // gracz vs ai lub ai vs gracz (wtedy ruch byl juz wczesniej)
            {
                if(board[colNumber][0] != 0) //jesli w kolumnie nie ma ju¿ miejsca na klocek
                    continue;
                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        cout << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                        board[colNumber][j] = RED;
                        --freeBlocks;
                        break;
                    }
                gui -> display(board);

                int isWon = checkWin();
                if(isWon || freeBlocks == 0) // jesli wygrana lub remis
                {






                    if(freeBlocks == 0 && !isWon)
                        cout << "DRAW" << endl;

                    cout << "END OF THE GAME" << endl;

                    while(1)
                    {
                        if(gui->getInput() == -1)
                            break;
                    }
                    break;
                }

                do
                {
                    colNumber = ai1 -> makeMove(board, YELLOW);
                }
                while(board[colNumber][0] != 0);

                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        cout << "Yellow on " << "\t" << colNumber << " " << j << endl;

                        board[colNumber][j] = YELLOW;
                        --freeBlocks;
                        break;
                    }
            }
            else if (mode == AIvsAI)    // ai kontra ai
            {
                do
                {
                    if(whoPlays) //jesli gra pierwszy gracz
                    {
                        ++ruchyCzerwonego;
                        auto startTime1 = std::chrono::high_resolution_clock::now();
                        colNumber = ai1 -> makeMove(board, RED);
                        auto stopTime1 = std::chrono::high_resolution_clock::now();
                        cout << "1. Czas rundy: " << std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime1-startTime1).count() << endl;
                        time1 += stopTime1 - startTime1;
                        cout << "2. Czas calosci ruchow czerwonego: " << std::chrono::duration_cast<std::chrono::nanoseconds>(time1).count() << endl;
                    }
                    else
                    {
                        ++ruchyZoltego;
                        auto startTime2 = std::chrono::high_resolution_clock::now();
                        colNumber = ai2 -> makeMove(board, YELLOW);
                        auto stopTime2 = std::chrono::high_resolution_clock::now();
                        cout << "1. Czas rundy: " << std::chrono::duration_cast<std::chrono::nanoseconds>(stopTime2-startTime2).count() << endl;
                        time2 += stopTime2 - startTime2;
                        cout << "2. Czas calosci ruchow zoltego: " << std::chrono::duration_cast<std::chrono::nanoseconds>(time2).count() << endl;
                    }
                }
                while(board[colNumber][0] != 0);

                for(int j = HEIGHT-1; j >= 0; --j)
                    if(board[colNumber][j] == 0)
                    {
                        if(whoPlays) //pierwszy gracz
                        {
                            cout << "Red on " << "\t" << "\t" << colNumber << " " << j << endl;
                            board[colNumber][j] = RED;
                            whoPlays = !whoPlays;
                            --freeBlocks;
                            break;
                        }
                        else //drugi gracz
                        {
                            cout << "Yellow on " << "\t" << colNumber << " " << j << endl;
                            board[colNumber][j] = YELLOW;
                            whoPlays = !whoPlays;
                            --freeBlocks;
                            break;
                        }
                    }
            }
            gui->display(board);

            int isWon = checkWin();
            if(isWon || freeBlocks == 0) // jesli wygrana lub remis
            {

                    fstream plik("out.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik <<
                        potrzebnyCzerwony << " " <<
                        potrzebnyZolty <<  " " <<
                        std::chrono::duration_cast<std::chrono::nanoseconds>(time1).count()  <<  " " <<
                        std::chrono::duration_cast<std::chrono::nanoseconds>(time2).count()  << " " <<
                        std::chrono::duration_cast<std::chrono::nanoseconds>(time1 + time2).count() <<  " " ;


                        if(freeBlocks == 0 && !isWon)
                        {
                            plik << 0 <<  " " ;
                        }
                        else
                            {
                            plik << isWon <<  " " ;
                            }

                        plik <<
                        ruchyCzerwonego << " " <<
                        ruchyZoltego << endl;


                        plik.close();
                    }



                if(freeBlocks == 0 && !isWon)
                    cout << "DRAW" << endl;

                cout << "END OF THE GAME" << endl;

              /*  while(1)
                {
                    if(gui->getInput() == -1)
                        break;
                }*/
                break;
            }
        }
    }
}


int Game::checkWin()
{
    int actual;
    for(int i = 0; i < WIDTH; ++i)   //4s vertically
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
                    return actual;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   //4s horizontally
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
                    return actual;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   //4s diagonally up-right
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
                    return actual;
                }
            }
    for(int i = 0; i < WIDTH-3; ++i)   // 4s diagonally down-right
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
                    return actual;
                }
            }
    return 0;
}
