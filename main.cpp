#include "Game.h"

using namespace std;

int main()
{
    int mode = 2;
    Game *game = new Game(mode);
    game->start();
    delete game;
    return 0;
}
END_OF_MAIN();
