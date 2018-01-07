#ifndef GAME_H
#define GAME_H

#include "Gui.h"
#include "AI.h"

#define WIDTH 7
#define HEIGHT 6
#define RED 1
#define YELLOW -1

using namespace std;

class Game
{
    int mode; //rozroznia tryb PvsAI (1), AIvsP (2), AIvsAI (3)
    int **board;
    bool whoPlays;

    Gui *gui;
    AI *ai;

public:
    Game();
    ~Game();

    void start();

private:
    bool checkWin();
};

#endif // GAME_H
