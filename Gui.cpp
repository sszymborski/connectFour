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
    mode_1 = load_bmp("manVSmac.bmp",default_palette);
    mode_2 = load_bmp("macVSman.bmp",default_palette);
    mode_3 = load_bmp("macVSmac.bmp",default_palette);
    install_mouse(); //mysz
    //select_mouse_cursor(MOUSE_CURSOR_BUSY); //inny kursor myszki
    show_mouse( screen ); //wyswietlanie myszy na ekranie
}

Gui::~Gui()
{
    destroy_bitmap( buffer ); //zwalanianie pamieci
    allegro_exit();
}

void Gui::mouse()
{
    if( mx != mouse_x || my != mouse_y || mb != mouse_b ) //stale przypisywanie wspolrzednych kursora i stanu przycisku do zmiennych
    {
        mx = mouse_x;
        my = mouse_y;
        mb = mouse_b;
    }
}

int Gui::showStartWindow() //funkcja obslugujaca mysz na ekranie
{
    scare_mouse();
    clear_to_color( buffer, makecol( 150, 150, 150 ) ); //kolor tla

    textprintf_centre_ex( buffer, font, 350, 80, makecol( 200, 200, 200 ), - 1, "HELLO");

    textprintf_centre_ex( buffer, font, 350, 150, makecol( 200, 200, 200 ), - 1, "CHOOSE GAME MODE");

    textprintf_ex( buffer, font, 105, 350, makecol( 200, 200, 200 ), - 1, "PLAYER VS AI");
    textprintf_ex( buffer, font, 305, 350, makecol( 200, 200, 200 ), - 1, "AI VS PLAYER");
    textprintf_ex( buffer, font, 520, 350, makecol( 200, 200, 200 ), - 1, "AI VS AI");

    masked_blit( mode_1, buffer, 0, 0, 100, 240, PUCK, PUCK );
    masked_blit( mode_2, buffer, 0, 0, 300, 240, PUCK, PUCK );
    masked_blit( mode_3, buffer, 0, 0, 500, 240, PUCK, PUCK );

    blit( buffer, screen, 0, 0, 0, 0, WIDTH*PUCK, HEIGHT*PUCK ); //przeniesienie z buffera na ekran
    unscare_mouse();
    // rest(250);
    while(!key[ KEY_ESC ])
    {
        mouse();
        // cout << mx << " " << my << endl;

        if(mb == 1)
        {
            if(mx > 90 && mx < 210 && my > 230 && my < 380)
                return PvsAI;
            if(mx > 290 && mx < 410 && my > 230 && my < 380)
                return AIvsP;
            if(mx > 490 && mx < 610 && my > 230 && my < 380)
                return AIvsAI;
        }
    }
    return -1;
}

int Gui::getInput() //funkcja obslugujaca mysz na ekranie
{
    if(key[ KEY_ESC ])
        return -1;

    mouse();

    int x = 0; // y = 0;
    if(mb == 1)
    {
        x = floor(mx/PUCK); //przerobienie pikseli na wspolrzedne pola
        //y = floor(my/PUCK);
        return x;
    }

    return -2; //nic sie nie stalo
}

void Gui::display(int **tab)
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
    rest(250);
    unscare_mouse();
}
