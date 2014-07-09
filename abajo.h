#ifndef ABAJO_H
#define ABAJO_H
#include "Enemies.h"

class abajo : public Enemies
{
    public:
        abajo(int x, int y, SDL_Surface *screen,SDL_Surface * surface);
        virtual ~abajo();
        void mover();
    protected:
    private:
};

#endif // ABAJO_H
