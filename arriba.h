#ifndef ARRIBA_H
#define ARRIBA_H
#include "Enemies.h"

class arriba : public Enemies
{
    public:
        arriba(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        virtual ~arriba();
        void mover();
    protected:
    private:
};

#endif // ARRIBA_H
