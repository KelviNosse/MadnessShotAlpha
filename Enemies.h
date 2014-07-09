#ifndef ENEMIES_H
#define ENEMIES_H
#include <SDL/SDL.h>
#include <iostream>

using namespace std;
class Enemies
{
    public:
            SDL_Surface * surface ;
            int x;
            int y;
            int morir;
            string tipo;
            SDL_Surface * screen;
             bool parp;
            bool borrar;
            bool shooting;
            bool where;
            bool powerup;
        Enemies(int x, int y, SDL_Surface *screen,SDL_Surface * surface,bool powerup);
        Enemies();
        void dibujar();
        virtual void mover(bool m);
        virtual void logica(int clickx, int clicky);
        void dib(SDL_Surface*d);
        void sumar();


        virtual ~Enemies();
    protected:
    private:
};

#endif // ENEMIES_H
