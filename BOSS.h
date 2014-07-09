#ifndef BOSS_H
#define BOSS_H
#include "Enemies.h"
#include "SDL/SDL_image.h"

class BOSS : public Enemies
{
    public:
        BOSS(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        virtual ~BOSS();
         void mover(bool m);
         void logica(int clickx,int clicky);
    protected:
    private:
};

#endif // BOSS_H
