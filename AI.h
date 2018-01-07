#ifndef AI_H
#define AI_H

#include <iostream>
#include <cstdlib>
#include <ctime>

#define VALUE4 1000
#define VALUE3 100
#define VALUE2 10
#define VALUE1 1
#define BADVALUE4 -9999
#define BADVALUE3 -1000
#define BADVALUE2 -10
#define BADVALUE1 -1

using namespace std;

class AI
{
    int depth;

public:
    AI(int depthArg);
    ~AI();

    int doRandMove();
    int makeMove(int** tab, int color);

private:
    int evaluate(int** tab, int color);
    bool checkWin(int** board);
    int alphabeta(int** tab, int color, bool whoPlays, int howDeep, int alphaArg, int betaArg);
};

#endif // AI_H
