#include "Game.h"

using namespace std;

int main(int argc, char **argv)
{
 /*   if(argc < 3)
    {
        cerr << "TOO FEW ARGUMENTS IN ./connectFour treeDepth1 treeDepth2" << endl;
        return -1;
    }
*/
    int depth1 = 1;   // atoi(argv[1]);
    int depth2 = 1;   //atoi(argv[2]);
    /*if(depth1 < 1 || depth2 < 1)
    {
        cerr << "INVALID ARGUMENT(S). MUST BE GREATER THAN 0!" << endl;
        return -2;
    }*/



    fstream plik("out.txt", ios::out | ios::app);
                    if(plik.good())
                    {
                        plik.seekp(0, ios_base::end);
                        plik <<
                        "GlebokoscC GlebkoscZ CzasC CzasZ Suma Wygrana RuchyC RuchyZ" << endl;
                        plik.close();
                    }




    for(int i = 1; i < 11; ++i)
    {
    Game *game = new Game(i, i);
    game->start();
    delete game;
    }


    return 0;
}
END_OF_MAIN();
