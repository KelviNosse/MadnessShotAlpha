#ifndef BOSSL2_H
#define BOSSL2_H
#include "Enemies.h"
#include "SDL/SDL_image.h"

class BOSSL2 : public Enemies
{
    public:
        BOSSL2(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        virtual ~BOSSL2();
         void mover(bool m);
         void logica(int clickx,int clicky);
    protected:
    private:
};

#endif // BOSSL2_H
