#include "derecha.h"

derecha::derecha(int x, int y, SDL_Surface *screen,SDL_Surface * surface, bool powerup)
{   this->x = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="d";
    this->morir =0;
    this->parp = true;
    this->where= true;
    this->shooting = false;
     this->powerup = powerup;
}

void derecha::mover(bool m){
if(m)
x-=4;
else
x+=4;
}
derecha::~derecha()
{
    //dtor
}
