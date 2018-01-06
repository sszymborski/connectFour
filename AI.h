#ifndef AI_H
#define AI_H

#include <iostream>
#include <cstdlib>
#include <ctime>

#define COUNT4 1000
#define COUNT3 100
#define COUNT2 10
#define COUNT1 1

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
};

#endif // AI_H
