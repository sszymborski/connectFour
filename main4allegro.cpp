#include <allegro.h>
#include <math.h>
#include <cstdlib>
#include <iostream>

#define SZEROKOSC 7
#define WYSOKOSC 6
#define KRATKA 100

using namespace std;

BITMAP * bufor = NULL;
BITMAP * czerwony = NULL;
BITMAP * zolty = NULL;
int mx, my, mb;
int tablicaDoGry[SZEROKOSC][WYSOKOSC];

void myszka() //funkcja obslugujaca mysz na ekranie
{
    if( mx != mouse_x || my != mouse_y || mb != mouse_b ) //stale przypisywanie wspolrzednych kursora i stanu przycisku do zmiennych
    {
        mx = mouse_x;
        my = mouse_y;
        mb = mouse_b;
    }
}

void czerwonyNaPole(int x, int y)
{
        masked_blit( czerwony, bufor, 0, 0, x*KRATKA, y*KRATKA, KRATKA, KRATKA );
}

void zoltyNaPole(int x, int y)
{
       masked_blit( zolty, bufor, 0, 0, x*KRATKA, y*KRATKA, KRATKA, KRATKA );
}

bool checkWinNow()   // tests whether someone has won on the board at the moment
{
    int actual;
    for(int i = 0; i < WYSOKOSC; ++i)   // tests 4 fields vertically to up
        for(int j = 0; j < 4; ++j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i][j+1] && actual == tablicaDoGry[i][j+2] && actual == tablicaDoGry[i][j+3])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i << "x" << j+1 <<", "
                    << i << "x" << j+2 <<", "
                    << i << "x" << j+3 << "."
                    << endl;
                    return true;
                }
            }
    for(int i = 0; i < 3; ++i)   // tests 4 fields horizontally to right
        for(int j = 0; j < 7; ++j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i+1][j] && actual == tablicaDoGry[i+2][j] && actual == tablicaDoGry[i+3][j])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j <<", "
                    << i+2 << "x" << j <<", "
                    << i+3 << "x" << j << "."
                    << endl;
                    return true;
                }
            }
    for(int i = 0; i < 3; ++i)   // tests 4 fields across to up and right
        for(int j = 0; j < 4; ++j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i+1][j+1] && actual == tablicaDoGry[i+2][j+2] && actual == tablicaDoGry[i+3][j+3])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j+1 <<", "
                    << i+2 << "x" << j+2 <<", "
                    << i+3 << "x" << j+3 << "."
                    << endl;
                    return true;
                }
            }
    for(int i = 0; i < 3; ++i)   // tests 4 fields across to down and right
        for(int j = 3; j < 7; ++j)
            if(tablicaDoGry[i][j] != 0)
            {
                actual = tablicaDoGry[i][j];
                if(actual == tablicaDoGry[i+1][j-1] && actual == tablicaDoGry[i+2][j-2] && actual == tablicaDoGry[i+3][j-3])
                {
                    cout << "Win by "
                    << i << "x" << j << ", "
                    << i+1 << "x" << j-1 <<", "
                    << i+2 << "x" << j-2 <<", "
                    << i+3 << "x" << j-3 << "."
                    << endl;
                    return true;
                }
            }

    return false;
}


int main()
{

    for(int i = 0; i < SZEROKOSC; ++i)
        for(int j = 0; j < WYSOKOSC; ++j)
            tablicaDoGry[i][j] = 0;

    mx = my = mb = 0;
    allegro_init();
    install_keyboard();
    set_color_depth( 32 ); //glebia koloru
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, SZEROKOSC*KRATKA, WYSOKOSC*KRATKA, 0, 0 ); //rozmiar okna

    clear_to_color( screen, makecol( 128, 128, 128 ) ); //kolor okna
    bufor = create_bitmap( SZEROKOSC*KRATKA, WYSOKOSC*KRATKA ); //rozmiar
    czerwony = load_bmp("czerwony.bmp",default_palette);
    zolty = load_bmp("zolty.bmp",default_palette);

    install_mouse(); //mysz
    //select_mouse_cursor(MOUSE_CURSOR_BUSY); //inny kursor myszki
    show_mouse( screen ); //wyswietlanie myszy na ekranie
    unscare_mouse();


    while( !key[ KEY_ESC ] ) //petla stale odsWiezajaca ekran
    {
        clear_to_color( bufor, makecol( 150, 150, 150 ) ); //kolor tla
        //textprintf_ex( bufor, font, 250, 40, makecol( 200, 200, 200 ), - 1, "GRAJ"); //napis
        //clear_to_color( bufor, makecol( 150, 150, 150 ) ); //kolor
        myszka();

        for(int i=1; i<WYSOKOSC; i++)
        {
            hline(bufor, 0, i*KRATKA, SZEROKOSC*KRATKA, makecol(255,255,255));  //rysowanie siatki pol
        }
        for(int i=1; i<SZEROKOSC; i++)
        {
            vline(bufor, i*KRATKA, 0, WYSOKOSC*KRATKA, makecol(255,255,255));
        }


                int x=NULL, y=NULL;
                if(mb==1)
                {
                    x=floor(mx/KRATKA); //przerobienie pikseli na wspolrzedne pola
                    y=floor(my/KRATKA);
                    cout << "czerwony na " << x << " " << y << endl;
                    tablicaDoGry[x][y]=1;
                }
                if(mb==2)
                {
                    x=floor(mx/KRATKA); //przerobienie pikseli na wspolrzedne pola
                    y=floor(my/KRATKA);
                    cout << "zolty na " << x << " " << y << endl;
                    tablicaDoGry[x][y]=-1;
                }

    for(int i = 0; i < SZEROKOSC; ++i)
        for(int j = 0; j < WYSOKOSC; ++j)
        {
            if(tablicaDoGry[i][j] == 1)
                czerwonyNaPole(i,j);
            else if(tablicaDoGry[i][j]==-1)
                zoltyNaPole(i,j);
        }

        checkWinNow();

        blit( bufor, screen, 0, 0, 0, 0, SZEROKOSC*KRATKA, WYSOKOSC*KRATKA ); //przeniesienie z bufora na ekran
        rest(100);
    }
    destroy_bitmap( bufor ); //zwalanianie pamieci


    allegro_exit();
}
END_OF_MAIN();
