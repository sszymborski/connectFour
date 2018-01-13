#ifndef GAME_H
#define GAME_H

#include "Gui.h"
#include "AI.h"
#include <fstream>

#define WIDTH 7
#define HEIGHT 6
#define RED 1
#define YELLOW -1
#define PvsAI 1
#define AIvsP 2
#define AIvsAI 3

using namespace std;

class Game
{
    int mode; //rozroznia tryb P vs AI (1), AI vs P (2), AI vs AI (3)
    int **board;
    bool whoPlays;

    Gui *gui;
    AI *ai1, *ai2;

public:
    Game(int depth1, int depth2);
    ~Game();

    void start();

private:
    bool checkWin();
};

#endif // GAME_H
