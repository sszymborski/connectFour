#include "Game.h"

using namespace std;

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        cerr << "TOO FEW ARGUMENTS IN ./connectFour treeDepth1 treeDepth2" << endl;
        return -1;
    }

    int depth1 = atoi(argv[1]);
    int depth2 = atoi(argv[2]);
    if(depth1 < 1 || depth2 < 1)
    {
        cerr << "INVALID ARGUMENT(S). MUST BE GREATER THAN 0!" << endl;
        return -2;
    }

    Game *game = new Game(depth1, depth2);
    game->start();
    delete game;

    return 0;
}
END_OF_MAIN();
