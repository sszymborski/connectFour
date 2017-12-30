#include "Gui.h"
#include "Gra.h"

#include <iostream>

Gui::Gui()
{
    bufor = czerwony = zolty = NULL;
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
}

Gui::~Gui()
{
    destroy_bitmap( bufor ); //zwalanianie pamieci
    allegro_exit();
}

int Gui::myszka(int **tab) //funkcja obslugujaca mysz na ekranie
{
    if(key[ KEY_ESC ])
        return -1;

    if( mx != mouse_x || my != mouse_y || mb != mouse_b ) //stale przypisywanie wspolrzednych kursora i stanu przycisku do zmiennych
    {
        mx = mouse_x;
        my = mouse_y;
        mb = mouse_b;
    }

    int x = 0, y = 0;

    if(mb == 1)
    {
        x = floor(mx/KRATKA); //przerobienie pikseli na wspolrzedne pola
        y = floor(my/KRATKA);

        if(tab[x][0] != 0) //jesli w kolumnie nie ma już miejsca na klocek
            return 0;
        else
            for(int j = WYSOKOSC-1; j >= 0; j--)
                if(tab[x][j] == 0)
                {
                    std::cout << "czerwony na " << x << " " << j << std::endl;
                    tab[x][j] = RED;
                    return 1;
                }
    }
    else if(mb == 2)
    {
        x = floor(mx/KRATKA); //przerobienie pikseli na wspolrzedne pola
        y = floor(my/KRATKA);

        if(tab[x][0] != 0) //jesli w kolumnie nie ma już miejsca na klocek
            return 0;
        else
            for(int j = WYSOKOSC-1; j >= 0; j--)
                if(tab[x][j] == 0)
                {
                    std::cout << "zolty na " << x << " " << j << std::endl;
                    tab[x][j] = YELLOW;
                    return 2;
                }
    }

    return 0;
}

void Gui::wyswietl(int **tab)
{
    scare_mouse();
    clear_to_color( bufor, makecol( 150, 150, 150 ) ); //kolor tla
    //textprintf_ex( bufor, font, 250, 40, makecol( 200, 200, 200 ), - 1, "GRAJ"); //napis
    //clear_to_color( bufor, makecol( 150, 150, 150 ) ); //kolor

    for(int i = 1; i < WYSOKOSC; i++)
    {
        hline(bufor, 0, i*KRATKA, SZEROKOSC*KRATKA, makecol(255,255,255));  //rysowanie siatki pol
    }
    for(int i = 1; i < SZEROKOSC; i++)
    {
        vline(bufor, i*KRATKA, 0, WYSOKOSC*KRATKA, makecol(255,255,255));
    }

    for(int i = 0; i < SZEROKOSC; ++i)
        for(int j = 0; j < WYSOKOSC; ++j)
        {
            if(tab[i][j] == RED)
                masked_blit( czerwony, bufor, 0, 0, i*KRATKA, j*KRATKA, KRATKA, KRATKA );
            else if(tab[i][j] == YELLOW)
                masked_blit( zolty, bufor, 0, 0, i*KRATKA, j*KRATKA, KRATKA, KRATKA );
        }

    blit( bufor, screen, 0, 0, 0, 0, SZEROKOSC*KRATKA, WYSOKOSC*KRATKA ); //przeniesienie z bufora na ekran
    rest(300);
    unscare_mouse();
}
