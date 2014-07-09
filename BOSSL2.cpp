#include "BOSSL2.h"

BOSSL2::BOSSL2(int x, int y, SDL_Surface *screen,SDL_Surface * surface)
{
     this->x = x;
    this->y = y;
    this->surface = surface;
    this->screen = screen;
    this->borrar = false;
    this->tipo="l";
    this->morir =0;
    this->parp = true;
    this->where= true;
    this->shooting = false;
}

void BOSSL2::mover(bool m){
if(m){
this->y+=25;
}

}

void BOSSL2::logica(int clickx, int clicky){
if(clickx>=x && clickx<=x+surface->w
                    &&clicky >=y&& clicky <=y+surface->h){
                    SDL_Rect offset;

                //Get offsets
                    offset.x = x;
                    offset.y = y;
    //Blit
            SDL_BlitSurface( IMG_Load("nightshadehit.png") , NULL, screen, &offset );
                    morir++;
                    if(morir==20)
                        borrar = true;
}


}

BOSSL2::~BOSSL2()
{
    //dtor
}
