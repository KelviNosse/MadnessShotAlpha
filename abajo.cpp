#include "abajo.h"

abajo::abajo(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
    this->x = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="ab";
    this->morir =0;
    this->parp = true;
     this->contador=80;
}
void abajo::mover(){
    y-=5;
}
abajo::~abajo()
{
    //dtor
}
