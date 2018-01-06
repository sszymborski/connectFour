#include "Game.h"

using namespace std;

int main()
{
    Game *game = new Game();
    game->start();
    delete game;

    return 0;
}
END_OF_MAIN();
