#include <iostream>
#include "Gra.h"
#include "Gui.h"

using namespace std;

int main()
{
    Gra *gra = new Gra();
    gra->graj();
    delete gra;

    return 0;
}
//END_OF_MAIN();
