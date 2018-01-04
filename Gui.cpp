#include "Gui.h"
#include "Game.h"

#include <iostream>

Gui::Gui()
{
    buffer = red = yellow = NULL;
    mx = my = mb = 0;
    allegro_init();
    install_keyboard();
    set_color_depth( 32 ); //glebia koloru
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, WIDTH*PUCK, HEIGHT*PUCK, 0, 0 ); //rozmiar okna
    clear_to_color( screen, makecol( 128, 128, 128 ) ); //kolor okna
    buffer = create_bitmap( WIDTH*PUCK, HEIGHT*PUCK ); //rozmiar
    red = load_bmp("red.bmp",default_palette);
    yellow = load_bmp("yellow.bmp",default_palette);
    install_mouse(); //mysz
    //select_mouse_cursor(MOUSE_CURSOR_BUSY); //inny kursor myszki
    show_mouse( screen ); //wyswietlanie myszy na ekranie
}

Gui::~Gui()
{
    destroy_bitmap( buffer ); //zwalanianie pamieci
    allegro_exit();
}

int Gui::mouse(int **tab) //funkcja obslugujaca mysz na ekranie
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
        x = floor(mx/PUCK); //przerobienie pikseli na wspolrzedne pola
        y = floor(my/PUCK);
        if(tab[x][0] != 0) //jesli w kolumnie nie ma ju¿ miejsca na klocek
            return 0;
        else
            for(int j = HEIGHT-1; j >= 0; j--)
                if(tab[x][j] == 0)
                {
                    cout << "Red on " << "\t" << "\t" << x << " " << j << endl;
                    tab[x][j] = RED;
                    return 1;
                }
    }
    else if(mb == 2)
    {
        x = floor(mx/PUCK); //przerobienie pikseli na wspolrzedne pola
        y = floor(my/PUCK);
        if(tab[x][0] != 0) //jesli w kolumnie nie ma ju¿ miejsca na klocek
            return 0;
        else
            for(int j = HEIGHT-1; j >= 0; j--)
                if(tab[x][j] == 0)
                {
                    cout << "Yellow on " << "\t" << x << " " << j << endl;
                    tab[x][j] = YELLOW;
                    return 2;
                }
    }
    return 0;
}

void Gui::show(int **tab)
{
    scare_mouse();
    clear_to_color( buffer, makecol( 150, 150, 150 ) ); //kolor tla
    //textprintf_ex( buffer, font, 250, 40, makecol( 200, 200, 200 ), - 1, "GRAJ"); //napis
    //clear_to_color( buffer, makecol( 150, 150, 150 ) ); //kolor
    for(int i = 1; i < HEIGHT; i++)
        hline(buffer, 0, i*PUCK, WIDTH*PUCK, makecol(255,255,255));  //rysowanie siatki pol
    for(int i = 1; i < WIDTH; i++)
        vline(buffer, i*PUCK, 0, HEIGHT*PUCK, makecol(255,255,255));

    for(int i = 0; i < WIDTH; ++i)
        for(int j = 0; j < HEIGHT; ++j)
            if(tab[i][j] == RED)
                masked_blit( red, buffer, 0, 0, i*PUCK, j*PUCK, PUCK, PUCK );
            else if(tab[i][j] == YELLOW)
                masked_blit( yellow, buffer, 0, 0, i*PUCK, j*PUCK, PUCK, PUCK );
    blit( buffer, screen, 0, 0, 0, 0, WIDTH*PUCK, HEIGHT*PUCK ); //przeniesienie z buffera na ekran
    rest(300);
    unscare_mouse();
}
