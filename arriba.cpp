#include "arriba.h"

arriba::arriba(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="ar";
    this->morir =0;
    this->parp = true;
     this->contador=70;
}

void arriba::mover(){
    y+=5;
}

arriba::~arriba()
{
    //dtor
}
