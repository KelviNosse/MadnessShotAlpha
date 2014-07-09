//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include "Enemies.h"
#include <list>
#include "derecha.h"
#include "abajo.h"
#include "arriba.h"
#include <sstream>
#include <fstream>
#include "SDL/SDL_ttf.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <list>
#include <algorithm>
#include <vector>
#include "BOSS.h"
#include "BOSSL2.h"


using namespace std;
//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;


int FRAMES_PER_SECOND =60 ;

//The surfaces
SDL_Surface *buttonSheet = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *seconds = NULL;
//The event structure
SDL_Surface *background = NULL;
SDL_Surface *infernobackg = NULL;
SDL_Surface *background3 = NULL;
SDL_Surface *hurt = NULL;
SDL_Surface *scr = NULL;
SDL_Event event;
stringstream stream;
SDL_Surface *score = NULL;
SDL_Surface *stage=NULL;
SDL_Surface* nothing = NULL;
SDL_Surface* text = NULL;
Mix_Chunk* slect = NULL;
Mix_Chunk* entergun = NULL;
Mix_Chunk* pwrup = NULL;
Mix_Chunk* reloading = NULL;
Mix_Chunk* firing = NULL;
Mix_Chunk* enemyshot = NULL;
Mix_Chunk* reloadvoice = NULL;
Mix_Chunk* miniondead = NULL;
Mix_Chunk* imgonnakillyou = NULL;
Mix_Chunk* coin = NULL;
Mix_Chunk* playerdead = NULL;
Mix_Music* stage1 = NULL;
Mix_Music* stage2 = NULL;
Mix_Music* stage3 = NULL;


TTF_Font *font = NULL;
TTF_Font *loadl = NULL;
SDL_Surface *back = NULL;
SDL_Surface *front = NULL;

list<int> puntaje;
list<int>puntaje1;
bool fullscreen = false;
bool shoted = false;
bool shoted2 = false;
bool flagp1 = false;
bool flagp2 = false;
bool stagekill = false;
int frameshot = 0;
int frameshot2 = 0;
int movereloadx = 620;

int scoreg=0;
//The surfaces
SDL_Surface *background1 = NULL;
SDL_Surface* shots[4];
SDL_Surface *stretch = NULL;
SDL_Surface* logos = NULL;
SDL_Surface* slides[3];
SDL_Surface* press = NULL;
SDL_Surface* play1 = NULL;
SDL_Surface* play2 = NULL;
SDL_Surface* options = NULL;
SDL_Surface* salir = NULL;
SDL_Surface* guntip = NULL;
SDL_Surface* layout = NULL;
SDL_Surface* samantha = NULL;
SDL_Surface* mad = NULL;
SDL_Surface* scroll = NULL;
SDL_Surface* p1 = NULL;
SDL_Surface* p2 = NULL;
SDL_Surface* p1icon = NULL;
SDL_Surface* p2icon = NULL;
SDL_Surface* stageclear = NULL;
SDL_Surface* scoretext = NULL;
SDL_Surface* lifetext = NULL;
SDL_Surface* reloadtext = NULL;



//The event structure

//The font
TTF_Font *fuente = NULL;
TTF_Font *fuentegae = NULL;
SDL_Surface* delay = NULL;




//The color of the font
SDL_Color textColorc = { 255, 255, 255 };



int x = 0, y = 0;

//The clip regions of the sprite sheet
SDL_Color textColor = { 0, 0, 0 };
class Timer
{
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};
Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}
//The button
class Button
{


private:
    //The attributes of the button
    SDL_Rect box;

    //The part of the button sprite sheet that will be shown
    SDL_Rect* clip;

public:
    //Initialize the variables
    int x;
    int y;
    Button( int x, int y, int w, int h);

    //Handles events and set the button's sprite region
    void handle_events();

    //Shows the button on the screen
    void show();
};

SDL_Surface *load_image( std::string filename )
{

    //Return the optimized surface
    return IMG_Load( filename.c_str() );

}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init()
{
    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }

    //Set up the screen

    // For windowed
    screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        return false;
    }

    if( TTF_Init() == -1 )
    {
        return false;
    }

    if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {

        return false;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Madness Shot Beta v1.0", NULL );

    //If everything initialized fine
    return true;
}

bool load_files()
{
    //Load the button sprite sheet background1 = load_image( "background1.png" );

    front = load_image("fade.png");

    scroll = load_image("scrollselect.png");
    infernobackg = load_image("infernostage.png");
    background3 = load_image("movetrain.png");
    p1 = load_image("samantha.png");
    p2 = load_image("mad.png");
    p1icon = load_image("samanicon.png");
    p2icon = load_image("madicon.png");
    stageclear = load_image("stageclear.png");
    shots[0] = load_image("shots0.png");
    shots[1] = load_image("shots1.png");
    shots[2] = load_image("shots2.png");
    shots[3] = load_image("shots3.png");
    back = load_image("strechy.png");
    delay = load_image("explode.png");
    slides[0] = load_image("slide0.png");
    slides[1] = load_image("slide1.png");
    slides[2] = load_image("slide2.png");
    guntip = load_image("tipweapon.png");
    scr = load_image("framescore.png");
    fuente = TTF_OpenFont( "nano.ttf", 25 );

    background1 = load_image("background1.png");
    //Open the font
    font = TTF_OpenFont( "fast_money.ttf", 19 );
    fuentegae = TTF_OpenFont("slkscreb.ttf", 36);
    loadl = TTF_OpenFont("loadl.ttf",70);
    buttonSheet = load_image( "button.png" );
    background = load_image("background.png");
    nothing = load_image("null.png");
    hurt = load_image("hurt.png");
    layout = load_image("layout.png");

    slect = Mix_LoadWAV("sounds/boop.wav.wav");
    entergun = Mix_LoadWAV("sounds/selectedshot.ogg");
    pwrup = Mix_LoadWAV("sounds/powerup.wav");
    firing = Mix_LoadWAV("sounds/fire.ogg");
    enemyshot = Mix_LoadWAV("sounds/shot.wav.wav");
    reloading = Mix_LoadWAV("sounds/reload.ogg");
    reloadvoice = Mix_LoadWAV("sounds/reloadvoice.ogg");
    miniondead = Mix_LoadWAV("sounds/miniondead.ogg");
    imgonnakillyou = Mix_LoadWAV("sounds/imgonnakillyou.ogg");
    coin = Mix_LoadWAV("sounds/coin");
    playerdead = Mix_LoadWAV("sounds/gameover.ogg");
    stage1 = Mix_LoadMUS("sounds/level1.ogg");
    stage2 = Mix_LoadMUS("sounds/level2.ogg");
    stage3 = Mix_LoadMUS("sounds/level3.ogg");

    //If there was a problem in loading the button sprite sheet
    if( buttonSheet == NULL )
    {
        return false;
    }
    if(font ==NULL)
        return false;

    //If everything loaded fine
    return true;
}

void clean_up()
{
    //Free the surface
    SDL_FreeSurface( buttonSheet );
    SDL_FreeSurface(background);
    SDL_FreeSurface(background1);
    SDL_FreeSurface( back );
    TTF_CloseFont( font );
    TTF_CloseFont( fuente );
    //Quit SDL_ttf
    TTF_Quit();

    Mix_CloseAudio();
    //Quit SDL
    SDL_Quit();
}



Button::Button( int x, int y,int w, int h)
{
    box.x =x;
    box.y = y;
    box.w = w;
    box.h = h;
}

void Button::handle_events()
{
    //The mouse offsets

    //If the mouse moved
    if( event.type == SDL_MOUSEMOTION )
    {
        //Get the mouse offsets
        x = event.motion.x;
        y = event.motion.y;

        box.x = x-18;
        box.y = y-18;

    }
    //If a mouse button was pressed
    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        //If the left mouse button was pressed
        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;


            //If the mouse is over the button


        }
    }

    //If a mouse button was released
    if( event.type == SDL_MOUSEBUTTONUP )
    {
        //If the left mouse button was released

        if( event.button.button == SDL_BUTTON_LEFT )
        {
            //Get the mouse offsets
            x = event.button.x;
            y = event.button.y;

            //If the mouse is over the button
            if( ( x > box.x ) && ( y > box.y ) )
            {
                //Set the button sprite

            }
        }


    }
}
void juego();
void MadnessMenu();
void pause()
{
    Mix_VolumeMusic(25);
    bool quit = false;
    bool cap = true;
    Timer fps;
    SDL_Surface* paus = load_image("pause.png");

    apply_surface(0, 0, paus, screen);
    while( quit == false )
    {
        cap = (!cap);
        fps.start();



        while( SDL_PollEvent( &event ) )
        {
            if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    Mix_VolumeMusic(60);
                    return;
                }
            }
        }

        if(SDL_Flip(screen) == -1)
        {

            return;
        }
        ;

        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

    }
}
void GameOver()
{
    Mix_HaltMusic();
    bool quit = false;
    bool cap = true;
    Timer fps;
    int animation = 0;
    int i = 0;
    SDL_Surface* gameover[6];
    gameover[0] = load_image("gameover0.png");
    gameover[1] = load_image("gameover1.png");
    gameover[2] = load_image("gameover2.png");
    gameover[3] = load_image("gameover3.png");
    gameover[4] = load_image("gameover4.png");
    gameover[5] = load_image("gameover5.png");
    Mix_PlayChannel(-1,playerdead,0);
    Mix_VolumeChunk(playerdead,80);



    while( quit == false )
    {
        cap = (!cap);
        fps.start();
        flagp1 = false;
        flagp2 = false;

        if(i%40 == 0)
        {

            if(animation<5)
            {
                animation++;
            }
        }

        apply_surface(0,0,gameover[animation],screen);


        while( SDL_PollEvent( &event ) )
        {
            if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    MadnessMenu();
                }
            }
        }

        i++;
        if(SDL_Flip(screen) == -1)
        {

            return;
        }
        ;

        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

    }


}
void guardarscores(int scor, string quien ){
if(quien == "mad.txt"){
    puntaje.push_back(scor);
    puntaje.sort();
    puntaje.reverse();
    ofstream in(quien.c_str());
    list<int>::iterator i=puntaje.begin();
    for (i=puntaje.begin(); i!=puntaje.end(); ++i)
    {
        in<<*i<<endl;
    }
}else if(quien =="samantha.txt"){
  puntaje1.push_back(scor);
    puntaje1.sort();
    puntaje1.reverse();
    ofstream in(quien.c_str());
    list<int>::iterator i=puntaje1.begin();
    for (i=puntaje1.begin(); i!=puntaje1.end(); ++i)
    {
        in<<*i<<endl;
    }

}
}
void rellenar()
{

    ifstream out("samantha.txt");
    int n;
    while(out>>n)
    {
        puntaje1.push_back(n);
    }
    ifstream ou("mad.txt");
    int y;
    while(ou>>y)
    {
        puntaje.push_back(y);
    }

}

void loadlevel1(){
bool quit=false;

Timer fps;
int frames=0;
int e=0;
SDL_Surface *loading[8];
loading[0]= load_image("loading0.png");
loading[1]= load_image("loading1.png");
loading[2]= load_image("loading2.png");
loading[3]= load_image("loading3.png");
loading[4]= load_image("loading4.png");
loading[5]= load_image("loading5.png");
loading[6]= load_image("loading6.png");
loading[7]= load_image("loading7.png");


int n = 0;
while( quit == false )
    {
        Mix_HaltMusic();
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }



        //Show the background
       stage= TTF_RenderText_Blended(loadl,"STAGE 1",textColorc);
       text = TTF_RenderText_Blended(fuente, "Click to Shoot Enemies, before they shoot you!",textColorc);
        apply_surface(0 , 0, loading[n], screen );
        apply_surface(220,100,stage,screen);
        apply_surface(10,380,text,screen);


        if(frames%15==0){
                n++;
                if(n>7){
                    n=0;
                    e++;
                }
        }
        if(e==5)
            juego();

        //Update the screen

        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }

            frames++;
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

}
void level2();
void loadlevel2(){
bool quit=false;

Timer fps;
int frames=0;
int e=0;
SDL_Surface *loading[8];
loading[0]= load_image("loading0.png");
loading[1]= load_image("loading1.png");
loading[2]= load_image("loading2.png");
loading[3]= load_image("loading3.png");
loading[4]= load_image("loading4.png");
loading[5]= load_image("loading5.png");
loading[6]= load_image("loading6.png");
loading[7]= load_image("loading7.png");
int n = 0;
while( quit == false )
    {
        Mix_HaltMusic();
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }



        //Show the background
       stage= TTF_RenderText_Blended(loadl,"STAGE 2",textColorc);
        apply_surface(0 , 0, loading[n], screen );
        apply_surface(220,100,stage,screen);
        text = TTF_RenderText_Blended(fuente, "Reload constantly to take advantage from enemies!",textColorc);
        apply_surface(0,380,text,screen);
        if(frames%15==0){
                n++;
                if(n>7){
                    n=0;
                    e++;
                }
        }
        if(e==5)
            level2();

        //Update the screen

        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }

            frames++;
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

}
void level3();
void loadlevel3(){
bool quit=false;

Timer fps;
int frames=0;
int e=0;
SDL_Surface *loading[8];
loading[0]= load_image("loading0.png");
loading[1]= load_image("loading1.png");
loading[2]= load_image("loading2.png");
loading[3]= load_image("loading3.png");
loading[4]= load_image("loading4.png");
loading[5]= load_image("loading5.png");
loading[6]= load_image("loading6.png");
loading[7]= load_image("loading7.png");
int n = 0;
while( quit == false )
    {
        Mix_HaltMusic();
        //Start the frame timer
        fps.start();

        //While there's events to handle
        while( SDL_PollEvent( &event ) )
        {
            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                quit = true;
            }
        }



        //Show the background
       stage= TTF_RenderText_Blended(loadl,"STAGE 3",textColorc);
        apply_surface(0 , 0, loading[n], screen );
        apply_surface(220,100,stage,screen);
        text = TTF_RenderText_Blended(fuente, "Avoid enemies from shooting you constantly!",textColorc);
        apply_surface(10,380,text,screen);
        if(frames%15==0){
                n++;
                if(n>7){
                    n=0;
                    e++;
                }
        }
        if(e==5)
            level3();

        //Update the screen

        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }

            frames++;
        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }

}

void level3(){

    int gastar = 0;
    bool nueva_carga = false;
    int reload = 33;
    SDL_Surface *bullet[32];
    int framegastar = 0;
    int finalscore = 0;
    bullet[0] = load_image("bullet0.png");
    bullet[1] = load_image("bullet1.png");
    bullet[2] = load_image("bullet2.png");
    bullet[3] = load_image("bullet3.png");
    bullet[4] = load_image("bullet4.png");
    bullet[5] = load_image("bullet5.png");
    bullet[6] = load_image("bullet6.png");
    bullet[7] = load_image("bullet7.png");
    bullet[8] = load_image("bullet8.png");
    bullet[9] = load_image("bullet9.png");
    bullet[10] = load_image("bullet10.png");
    bullet[11] = load_image("bullet11.png");
    bullet[12] = load_image("bullet12.png");
    bullet[13] = load_image("bullet13.png");
    bullet[14] = load_image("bullet14.png");
    bullet[15] = load_image("bullet15.png");
    bullet[16] = load_image("bullet16.png");
    bullet[17] = load_image("bullet17.png");
    bullet[18] = load_image("bullet18.png");
    bullet[19] = load_image("bullet19.png");
    bullet[20] = load_image("bullet20.png");
    bullet[21] = load_image("bullet21.png");
    bullet[22] = load_image("bullet22.png");
    bullet[23] = load_image("bullet23.png");
    bullet[24] = load_image("bullet24.png");
    bullet[25] = load_image("bullet25.png");
    bullet[26] = load_image("bullet26.png");
    bullet[27] = load_image("bullet27.png");
    bullet[28] = load_image("bullet28.png");
    bullet[29] = load_image("bullet29.png");
    bullet[30] = load_image("bullet30.png");
    bullet[31] = load_image("bullet31.png");

    int animgastar1 = 0;
    int animgastar2 = 3;
    int animgastar3 = 6;
    int animgastar4 = 9;
    int animgastar5 = 12;
    int animgastar6 = 15;
    int animgastar7 = 18;
    int animgastar8 = 21;
    int animgastar9 = 25;
    int animgastar10 = 28;
    int animgastar11 = 31;

    SDL_ShowCursor(0);
    SDL_Surface*enemy[5];
    enemy[0]= load_image("running0.png");
    enemy[1]= load_image("running1.png");
    enemy[2]=load_image("enemyhit0.png");
    enemy[3]=load_image("enemyhit1.png");
    enemy[4]=load_image("dead0.png");


    SDL_Surface *en[2];
    en[0]= load_image("running2.png");
    en[1]= load_image("running3.png");

    SDL_Surface *shoot[4];
    shoot[0]= load_image("enemies0.png");
    shoot[1]= load_image("enemies1.png");
    shoot[2]= load_image("enemies2.png");
    shoot[3]= load_image("enemies3.png");

    SDL_Surface * Bt[8];
    Bt[0] = load_image("transport0.png");
    Bt[1] = load_image("transport1.png");
    Bt[2] = load_image("transport2.png");
    Bt[3] = load_image("transport3.png");
    Bt[4] = load_image("transport4.png");
    Bt[5] = load_image("transport5.png");
    Bt[6] = load_image("transport6.png");
    Bt[7] = load_image("transport7.png");

    SDL_Surface * Bsh[7];
    Bsh[0] = load_image("bosshot0.png");
    Bsh[1] = load_image("bosshot1.png");
    Bsh[2] = load_image("bosshot2.png");
    Bsh[3] = load_image("bosshot3.png");
    Bsh[4] = load_image("bosshot4.png");
    Bsh[5] = load_image("bosshot5.png");
    Bsh[6] = load_image("bosshot6.png");

    SDL_Surface * Bn[4];
    Bn[0] = load_image("nightshadefall.png");
    Bn[1] = load_image("nightshade0.png");
    Bn[2] = load_image("nightshade1.png");
    Bn[3] = load_image("nightshade2.png");



    //Quit flag

    SDL_Surface *lifebar[9];
    lifebar[0] = load_image("lifebar0.png");
    lifebar[1] = load_image("lifebar1.png");
    lifebar[2] = load_image("lifebar2.png");
    lifebar[3] = load_image("lifebar3.png");
    lifebar[4] = load_image("lifebar4.png");
    lifebar[5] = load_image("lifebar5.png");
    lifebar[6] = load_image("lifebar6.png");
    lifebar[7] = load_image("lifebar7.png");
    lifebar[8] = load_image("lifebar8.png");


    SDL_Surface *pwup[3];
    pwup[0] = load_image("health0.png");
    pwup[1] = load_image("health1.png");
    pwup[2] = load_image("health3.png");

    SDL_Surface *pwr[3];
    pwr[0] = load_image("health4.png");
    pwr[1] = load_image("health5.png");
    pwr[2] = load_image("health6.png");

    bool quit = false;


    int life =0;
    srand(time(NULL));
    //Make the button
    Button myButton(120,120,277,229);
    int frames=0;
    list<Enemies*>enem;
    bool izq= true;
    bool der = true;
    bool paused = false;
    bool reloadsound = false;
    Uint32 startin =0;
    Timer fps;
    int shotanim = 0;
    int boss = false;
    int m=0;
    int percent = 0;
    int sh =0;
    int n=0;
    int d=0;
    int iz=0;
    int transport =0;
    int bs =0;
    int bl = 1;
    int animate = 0;
    bool bossy= false;
    bool destroyb = false;
    bool destroyl = false;
    Timer myTimer;
    myTimer.start();
    bool appear = false;
    bool flagizq = false;
    bool flagder = false;
    int s=0;
    bool up = true;
    int pw=0;
    bool ap = false;
    bool b=true;
    SDL_Surface *hit[2];
    hit[0]= load_image("hitit.png");
    hit[1]= load_image("hitit2.png");
    int p =0;
    bool c = false;
    while( quit == false )
    {
        if(Mix_PlayingMusic() == 0){
            Mix_PlayMusic(stage3,-1);
            Mix_VolumeMusic(60);
        }
        paused = true;
        fps.start();


        if(frames%10 == 0)
        {

            animate++;
            if(animate>1)
                animate = 0;


        }

        if(bossy)
        {
            if(b)
            {
                if(!stagekill)
                {

                    enem.push_back((new BOSS(SCREEN_WIDTH/2,240,screen,Bt[0])));
                    enem.push_back((new BOSSL2(200,10,screen,Bn[0])));
                    b = false;
                }
            }
        }
        if(frames%377 == 0 && izq)
        {
            if(!stagekill)
            {

                if(!flagizq)
                    enem.push_back(new Enemies(0,360,screen,enemy[0],false));
                else
                    enem.push_back(new Enemies(0,350,screen,enemy[0],false));

            }
            flagizq=!flagizq;
            if(iz==2)
            {

                izq=false;

            }

            iz++;
        }
        if(frames%677==0 && der)
        {
            if(!stagekill)
            {

                if(!flagder)
                    enem.push_back(new derecha(560,340,screen,en[0],false));
                else
                    enem.push_back(new derecha(560,330,screen,en[0],false));

            }
            flagder =!flagder;
            d++;
            if(!boss)
            {
                if(d==2 )
                    der=false;
            }
            else if(boss)
            {
                if(d==1 )
                    der=false;
            }
        }
        if(bossy)
        {
            if(up)
            {
                if(!stagekill)
                {

                    enem.push_back(new Enemies(0,360,screen,enemy[0],true));
                    up = false;
                    ap = true;
                    c = true;
                }
            }


        }


        int clickx =-1;
        int clicky= -1;
        int xb = 0, yb = 0;
        while( SDL_PollEvent( &event ) )
        {
            //Handle button events
            myButton.handle_events();
            if(!stagekill)
            {
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (gastar <= 10)
                    {
                        if(event.button.button == SDL_BUTTON_LEFT)
                        {
                            Mix_PlayChannel( -1, firing, 0 );
                            Mix_VolumeChunk(firing, 50);
                            clickx = event.button.x;
                            clicky = event.button.y;
                            shoted = true;
                            frameshot = 0;
                            gastar++;
                            animgastar1 = 0;
                            animgastar2 = 3;
                            animgastar3 = 6;
                            animgastar4 = 9;
                            animgastar5 = 12;
                            animgastar6 = 15;
                            animgastar7 = 18;
                            animgastar8 = 21;
                            animgastar9 = 24;
                            animgastar10 = 27;
                            animgastar11 = 30;
                            framegastar = 0;
                            if (gastar > 32)
                                gastar = 32;

                        }
                    }
                }

            }


            //If the mouse moved
            if( event.type == SDL_MOUSEMOTION )
            {
                //Get the mouse offsets
                xb = event.motion.x;
                yb = event.motion.y;

                //If the mouse is over the button
                if( ( xb > 580 ) && ( xb < 580 + hit[0]->w ) && ( yb > 130 ) && ( yb < 130 +hit[0]->h ) )
                {
                    if(!reloadsound)
                    {
                        Mix_PlayChannel( -1, reloading, 0 );
                        Mix_VolumeChunk(reloading, 80);
                        reloadsound = true;

                    }

                    nueva_carga = true;
                }
                else
                    reloadsound = false;


            }

            if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    myTimer.pause();
                    pause();
                    myTimer.unpause();
                }
            }


            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                stagekill = false;
                flagp1 = false;
                flagp2 = false;
                quit = true;
            }

        }
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        apply_surface(0,0,infernobackg,screen);
        apply_surface(0,0,layout,screen);
        apply_surface(450,0,lifebar[life],screen);
        if(flagp1)
            apply_surface(450,0,p1icon,screen);
        if(flagp2)
            apply_surface(450,0,p2icon,screen);
        if(gastar==11){
            reloadtext = TTF_RenderText_Blended(fuentegae,"RELOAD",{255,rand()%100+1,0});
            apply_surface(580,130,hit[animate],screen);
            apply_surface(movereloadx,220,reloadtext,screen);
            if(movereloadx!=380)
                movereloadx-=8;
            else
                movereloadx == 380;

            if(frames%80 == 0){
                    Mix_PlayChannel( 1, reloadvoice, 0 );
                    Mix_VolumeChunk(reloadvoice, 80);
            }




            }


        list<Enemies*>::iterator i=enem.begin();
        while(i!=enem.end())
        {

            if((*i)->borrar)
            {
                shoted2 = true;
                s+=100;
                if((*i)->tipo=="n")
                {
                    Mix_PlayChannel( 1, miniondead, 0 );
                    Mix_VolumeChunk(miniondead, 100);
                    iz--;
                    if(iz==0)
                        izq= true;
                    if((*i)->powerup)
                    {
                        life=0;
                        pwr[p];

                    }
                    (*i)->dib(enemy[4]);
                }
                if((*i)->tipo=="d")
                {
                    Mix_PlayChannel( 1, miniondead, 0 );
                    Mix_VolumeChunk(miniondead, 100);
                    d--;
                    if(d==0)
                        der= true;
                    (*i)->dib(enemy[4]);

                }

                if((*i)->tipo=="b")
                {

                    destroyb = true;


                }

                if((*i)->tipo=="l")
                {

                    destroyl = true;


                }

                if(destroyb && destroyl)
                    stagekill = true;



                (*i)->where= true;
                Enemies*temp = (*i);
                i = enem.erase(i);


                delete temp;

            }
            else
            {

                if((*i)->tipo == "b" && bossy)
                {
                    (*i)->dib(Bt[transport]);
                }
                else
                {
                    if((*i)->tipo == "b" && boss)
                    {
                        (*i)->dib(Bsh[bs]);
                        if(bs==6 && frames%60==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;

                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);
                                    if(life==8)
                                    {
                                    if(flagp1)
                                        guardarscores(scoreg,"samantha.txt");
                                        else if (flagp2)
                                        guardarscores(scoreg,"mad.txt");
                                        flagp1 = false;
                                        flagp2 = false;
                                        GameOver();
                                    }
                                }
                            }

                        }

                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }


                        if((*i)->morir%15==0)
                        {
                            (*i)->dib(Bt[7]);
                            (*i)->dib(Bt[6]);
                            (*i)->dib(Bt[5]);
                            (*i)->dib(Bt[4]);
                            (*i)->dib(Bt[3]);
                            (*i)->dib(Bt[2]);
                            (*i)->dib(Bt[1]);
                            (*i)->dib(Bt[0]);
                            srand(time(NULL));
                            (*i)->mover(rand()%2);
                            (*i)->morir++;
                            bossy = true;

                        }



                    }
                }

                   if((*i)->tipo == "l")
                    {
                        if((*i)->y<240){
                        (*i)->mover(true);
                        (*i)->dib(Bn[0]);
                        }else{
                            (*i)->dib(Bn[bl]);
                        }
                        if(bl==3&& frames%60==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;

                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);
                                    if(life==8)
                                    {
                                    if(flagp1)
                                        guardarscores(scoreg,"samantha.txt");
                                        else if (flagp2)
                                        guardarscores(scoreg,"mad.txt");
                                        flagp1 = false;
                                        flagp2 = false;
                                        GameOver();
                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }




                    }

                if((*i)->tipo=="n")
                {


                    if((*i)->where && (*i)->x<=560 )
                    {
                        if((*i)->x==560)
                            (*i)->where = false;
                    }
                    if((*i)->x==0 )
                    {
                        (*i)->where = true;

                    }
                    if(!(*i)->shooting)
                        (*i)->mover((*i)->where);
                    if((*i)->morir== 2 && (*i)->powerup)
                    {
                        (*i)->dib(pwup[pw]);
                    }
                    else if((*i)->shooting)
                    {
                        (*i)->dib(shoot[sh]);
                        if(sh==3 && frames%15==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;

                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);
                                    if(life==8)
                                    {
                                    if(flagp1)
                                        guardarscores(scoreg,"samantha.txt");
                                        else if (flagp2)
                                        guardarscores(scoreg,"mad.txt");
                                        flagp1 = false;
                                        flagp2 = false;
                                        GameOver();

                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }

                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit1.png"));
                            (*i)-> parp =false;
                        }
                    }
                    else if((*i)->where)
                    {
                        (*i)->dib(enemy[m]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit0.png"));
                            (*i)-> parp =false;
                        }
                    }
                    else
                    {
                        (*i)->dib(en[m]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit3.png"));
                            (*i)-> parp =false;
                        }
                    }

                }
                else if((*i)->tipo == "d")
                {
                    if((*i)->where && (*i)->x>=0 )
                    {
                        if((*i)->x==0)
                            (*i)->where = false;
                    }
                    if((*i)->x>560 )
                    {
                        (*i)->where = true;
                    }
                    if(!(*i)->shooting)
                        (*i)->mover((*i)->where);
                    if((*i)->shooting)
                    {
                        (*i)->dib(shoot[sh]);
                        if(sh==3 && frames%15==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;
                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);

                                    if(life==8)
                                    {
                                        if(flagp1)
                                        guardarscores(scoreg,"samantha.txt");
                                        else if (flagp2)
                                        guardarscores(scoreg,"mad.txt");
                                        flagp1 = false;
                                        flagp1 = false;
                                        GameOver();
                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }


                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit2.png"));
                            (*i)-> parp =false;
                        }


                    }
                    else if((*i)->where)
                    {
                        (*i)->dib(en[n]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit3.png"));
                            (*i)-> parp =false;
                        }
                    }
                    else
                    {
                        (*i)->dib(enemy[n]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit0.png"));
                            (*i)-> parp =false;
                        }
                    }



                }

                if(frames>5)
                {
                    if(frames%255==0 && (*i)->tipo =="n")
                        (*i)->shooting =true;
                    else if(frames%355==0 && (*i)->tipo =="d")
                        (*i)->shooting =true;
                    (*i)->logica(clickx,clicky);

                }

            }

            i++;
        }



        //Show the button
        myButton.show();
        if(frames%150==0)
        {
            if(ap)
                pw++;
            if(pw>2)
            {
                pw=2;
                ap=false;

            }

            if(c)
                p++;
            if(p>2)
            {
                p=2;
                c= false;
            }


        }
        if(frames%15==0)
        {
            m++;
            sh++;
            n++;
            bs++;
            bl++;
            if(bossy)
                transport++;
            if(m>1)
                m=0;
            if(sh>3)
                sh=0;
            if(n>1)
                n=0;

            if(transport >7 )
            {
                bossy =false;
                transport=0;
            }
            if(bs>6)
                bs=0;
            if(bl>3)
                bl = 1;
        }

        if(frames%30)
        {
            if(shotanim < 3)
            {

                shotanim++;
            }

        }
        //Update the screen


        frames++;
        std::stringstream puntaje;
        int actualscore = s;
        puntaje<<"Score : "<<actualscore;
        score= TTF_RenderText_Solid( fuente,puntaje.str().c_str(), {255,255,255} );
        apply_surface(  0, 0, score, screen );
        if(stagekill)
        {



            apply_surface(0,0,stageclear,screen);


                if(flagp1)
                    apply_surface(250,230,p1,screen);
                if(flagp2)
                    apply_surface(240,250,p2,screen);

                if(life == 0)
                {
                    if(finalscore<500){
                        finalscore+=50;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 500;

                    percent = 100;


                }

                if(life == 1)
                {
                    if(finalscore<400){
                        finalscore+=20;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 400;

                    percent = 80;

                }
                if(life == 2)
                {
                    if(finalscore<300){
                        finalscore+=100;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 300;

                    percent = 60;
                }
                if(life == 3)
                {
                    if(finalscore<200){
                        finalscore+=2;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 200;

                    percent = 45;
                }
                if(life == 4)
                {
                    if(finalscore<100){
                        finalscore+=5;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 100;

                    percent = 30;
                }
                if(life == 5)
                {
                    if(finalscore<50){
                        finalscore+=2;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 50;
                    percent = 20;
                }
                if(life == 6)
                {
                    if(finalscore<25){
                        finalscore+=1;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 25;

                    percent = 10;
                }
                if(life == 7)
                {
                    if(finalscore<10){
                        finalscore++;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 10;


                    percent = 5;
                }




                int totaladd = finalscore+s;
                std::stringstream points;
                std::stringstream lifepoints;

                points<<"Final Score : "<<totaladd;
                lifepoints<<"Health : "<<percent<<"%";
                scoretext= TTF_RenderText_Solid( fuente,points.str().c_str(), {255,255,255} );
                lifetext = TTF_RenderText_Solid( fuente,lifepoints.str().c_str(), {255,255,255} );
                apply_surface(160,150, scoretext, screen );
                apply_surface(160,200,lifetext,screen);
                  while(SDL_PollEvent(&event))
        {


               if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                                        scoreg+=totaladd;
                                        if(flagp1)
                                        guardarscores(scoreg,"samantha.txt");
                                        else if (flagp2)
                                        guardarscores(scoreg,"mad.txt");

                            flagp1 = false;
                            flagp2 = false;
                            stagekill = false;
                            MadnessMenu();


                    }

                }




        }



        }
        if(!boss)
        {
            std::stringstream time;
            if((60 - ((myTimer.get_ticks()-startin)/1000))>=10)
                time <<60 - ((myTimer.get_ticks()-startin)/1000);
            else if((60 - ((myTimer.get_ticks()-startin)/1000))<10)
                time <<"0"<<60 - ((myTimer.get_ticks()-startin)/1000);
            seconds = TTF_RenderText_Solid( fuentegae, time.str().c_str(), textColor );
            apply_surface( 292, 25, seconds, screen );

        }
        if (nueva_carga)
        {
            animgastar1 = 0;
            animgastar2 = 3;
            animgastar3 = 6;
            animgastar4 = 9;
            animgastar5 = 12;
            animgastar6 = 15;
            animgastar7 = 18;
            animgastar8 = 21;
            animgastar9 = 24;
            animgastar10 = 27;
            animgastar11 = 30;
            framegastar = 0;
            gastar = 0;
            apply_surface(530,20, bullet[0], screen);
            nueva_carga=false;
        }


        if (gastar == 0)
        {
            apply_surface(530,20, bullet[0], screen);
        }

        if (gastar == 1 )
        {

            apply_surface(530,20,bullet[animgastar1],screen);
            if (framegastar % 5 == 0)
                animgastar1++;
            framegastar++;

            if(animgastar1 > 3)
            {
                animgastar1 = 3;
            }

        }
        if (gastar == 2)
        {
            apply_surface(530,20,bullet[animgastar2],screen);
            if (framegastar % 5 == 0)
                animgastar2++;
            framegastar++;

            if(animgastar2 > 6)
            {
                animgastar2 = 6;
            }

        }
        if (gastar == 3)
        {
            apply_surface(530,20,bullet[animgastar3],screen);
            if (framegastar % 5 == 0)
                animgastar3++;
            framegastar++;

            if(animgastar3 > 9)
            {
                animgastar3 = 9;
            }

        }
        if (gastar == 4)
        {
            apply_surface(530,20,bullet[animgastar4],screen);
            if (framegastar % 5 == 0)
                animgastar4++;
            framegastar++;

            if(animgastar4 > 12)
            {
                animgastar4 = 12;
            }

        }
        if (gastar == 5)
        {
            apply_surface(530,20,bullet[animgastar5],screen);
            if (framegastar % 5 == 0)
                animgastar5++;
            framegastar++;

            if(animgastar5 > 15)
            {
                animgastar5 = 15;
            }

        }
        if (gastar == 6)
        {
            apply_surface(530,20,bullet[animgastar6],screen);
            if (framegastar % 5 == 0)
                animgastar6++;
            framegastar++;

            if(animgastar6 > 18)
            {
                animgastar6 = 18;
            }

        }
        if (gastar == 7)
        {
            apply_surface(530,20,bullet[animgastar7],screen);
            if (framegastar % 5 == 0)
                animgastar7++;
            framegastar++;

            if(animgastar7 > 21)
            {
                animgastar7 = 21;
            }

        }
        if (gastar == 8)
        {
            apply_surface(530,20,bullet[animgastar8],screen);
            if (framegastar % 5 == 0)
                animgastar8++;
            framegastar++;

            if(animgastar8 > 24)
            {
                animgastar8 = 24;
            }

        }
        if (gastar == 9)
        {
            apply_surface(530,20,bullet[animgastar9],screen);
            if (framegastar % 5 == 0)
                animgastar9++;
            framegastar++;

            if(animgastar9 > 27)
            {
                animgastar9 = 27;
            }

        }
        if (gastar == 10)
        {
            apply_surface(530,20,bullet[animgastar10],screen);
            if (framegastar % 5 == 0)
                animgastar10++;
            framegastar++;

            if(animgastar10 > 30)
            {
                animgastar10 = 30;
            }

        }
        if (gastar == 11)
        {
            apply_surface(530,20,bullet[animgastar11],screen);
            if (framegastar % 5== 0)
                animgastar11++;
            framegastar++;

            if(animgastar11 > 32)
            {
                animgastar11 = 32;
            }

        }


        if(((myTimer.get_ticks()-startin)/1000)==60)
        {
            boss = true;
            bossy =true;
            //quit = true;
        }





        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

        //Fill the screen white




    }






}



void level2(){
    int bgX=0;
    int bgY=0;
    int eny = 160;
    int gastar = 0;
    bool nueva_carga = false;
    int reload = 33;
    SDL_Surface *bullet[32];
    int framegastar = 0;
    int finalscore = 0;
    bullet[0] = load_image("bullet0.png");
    bullet[1] = load_image("bullet1.png");
    bullet[2] = load_image("bullet2.png");
    bullet[3] = load_image("bullet3.png");
    bullet[4] = load_image("bullet4.png");
    bullet[5] = load_image("bullet5.png");
    bullet[6] = load_image("bullet6.png");
    bullet[7] = load_image("bullet7.png");
    bullet[8] = load_image("bullet8.png");
    bullet[9] = load_image("bullet9.png");
    bullet[10] = load_image("bullet10.png");
    bullet[11] = load_image("bullet11.png");
    bullet[12] = load_image("bullet12.png");
    bullet[13] = load_image("bullet13.png");
    bullet[14] = load_image("bullet14.png");
    bullet[15] = load_image("bullet15.png");
    bullet[16] = load_image("bullet16.png");
    bullet[17] = load_image("bullet17.png");
    bullet[18] = load_image("bullet18.png");
    bullet[19] = load_image("bullet19.png");
    bullet[20] = load_image("bullet20.png");
    bullet[21] = load_image("bullet21.png");
    bullet[22] = load_image("bullet22.png");
    bullet[23] = load_image("bullet23.png");
    bullet[24] = load_image("bullet24.png");
    bullet[25] = load_image("bullet25.png");
    bullet[26] = load_image("bullet26.png");
    bullet[27] = load_image("bullet27.png");
    bullet[28] = load_image("bullet28.png");
    bullet[29] = load_image("bullet29.png");
    bullet[30] = load_image("bullet30.png");
    bullet[31] = load_image("bullet31.png");

    int animgastar1 = 0;
    int animgastar2 = 3;
    int animgastar3 = 6;
    int animgastar4 = 9;
    int animgastar5 = 12;
    int animgastar6 = 15;
    int animgastar7 = 18;
    int animgastar8 = 21;
    int animgastar9 = 25;
    int animgastar10 = 28;
    int animgastar11 = 31;

    SDL_ShowCursor(0);
    SDL_Surface*enemy[5];
    enemy[0]= load_image("running0.png");
    enemy[1]= load_image("running1.png");
    enemy[2]=load_image("enemyhit0.png");
    enemy[3]=load_image("enemyhit1.png");
    enemy[4]=load_image("dead0.png");


    SDL_Surface *en[2];
    en[0]= load_image("running2.png");
    en[1]= load_image("running3.png");

    SDL_Surface *shoot[4];
    shoot[0]= load_image("enemies0.png");
    shoot[1]= load_image("enemies1.png");
    shoot[2]= load_image("enemies2.png");
    shoot[3]= load_image("enemies3.png");



    SDL_Surface * Bsh[4];
    Bsh[0] = load_image("nightshadefall.png");
    Bsh[1] = load_image("nightshade0.png");
    Bsh[2] = load_image("nightshade1.png");
    Bsh[3] = load_image("nightshade2.png");


    SDL_Surface *lifebar[9];
    lifebar[0] = load_image("lifebar0.png");
    lifebar[1] = load_image("lifebar1.png");
    lifebar[2] = load_image("lifebar2.png");
    lifebar[3] = load_image("lifebar3.png");
    lifebar[4] = load_image("lifebar4.png");
    lifebar[5] = load_image("lifebar5.png");
    lifebar[6] = load_image("lifebar6.png");
    lifebar[7] = load_image("lifebar7.png");
    lifebar[8] = load_image("lifebar8.png");


    SDL_Surface *pwup[3];
    pwup[0] = load_image("health0.png");
    pwup[1] = load_image("health1.png");
    pwup[2] = load_image("health3.png");

    SDL_Surface *pwr[3];
    pwr[0] = load_image("health4.png");
    pwr[1] = load_image("health5.png");
    pwr[2] = load_image("health6.png");

    bool quit = false;


    int life =0;
    srand(time(NULL));
    //Make the button
    Button myButton(120,120,277,229);
    int frames=0;
    list<Enemies*>enem;
    bool izq= true;
    bool der = true;
    bool paused = false;
    bool reloadsound = false;
    Uint32 startin =0;
    Timer fps;
    int shotanim = 0;
    int boss = false;
    int m=0;
    int percent = 0;
    int sh =0;
    int n=0;
    int d=0;
    int iz=0;
    int transport =0;
    int bs =1;
    int animate = 0;
    bool bossy= false;
    Timer myTimer;
    myTimer.start();
    bool appear = false;
    bool flagizq = false;
    bool flagder = false;
    int s=0;
    bool up = true;
    int pw=0;
    bool ap = false;
    bool b=true;
    SDL_Surface *hit[2];
    hit[0]= load_image("hitit.png");
    hit[1]= load_image("hitit2.png");
    int p =0;
    bool c = false;
    while( quit == false )
    {

        if(Mix_PlayingMusic() == 0){
            Mix_PlayMusic(stage2,-1);
            Mix_VolumeMusic(60);
        }
        paused = true;
        fps.start();


        if(frames%10 == 0)
        {

            animate++;
            if(animate>1)
                animate = 0;


        }

        if(bossy)
        {
            if(b)
            {
                if(!stagekill)
                {

                    enem.push_back((new BOSSL2(SCREEN_WIDTH/2,10,screen,Bsh[0])));
                    b = false;
                }
            }
        }
        if(frames%100== 0 )
        {
            if(!stagekill)
            {


                    enem.push_back(new Enemies(10,165,screen,enemy[0],false));
                izq=false;

            }




        }



        int clickx =-1;
        int clicky= -1;
        int xb = 0, yb = 0;
        while( SDL_PollEvent( &event ) )
        {
            //Handle button events
            myButton.handle_events();
            if(!stagekill)
            {
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (gastar <= 10)
                    {
                        if(event.button.button == SDL_BUTTON_LEFT)
                        {
                            Mix_PlayChannel( -1, firing, 0 );
                            Mix_VolumeChunk(firing, 50);
                            clickx = event.button.x;
                            clicky = event.button.y;
                            shoted = true;
                            frameshot = 0;
                            gastar++;
                            animgastar1 = 0;
                            animgastar2 = 3;
                            animgastar3 = 6;
                            animgastar4 = 9;
                            animgastar5 = 12;
                            animgastar6 = 15;
                            animgastar7 = 18;
                            animgastar8 = 21;
                            animgastar9 = 24;
                            animgastar10 = 27;
                            animgastar11 = 30;
                            framegastar = 0;
                            if (gastar > 32)
                                gastar = 32;

                        }
                    }
                }

            }


            //If the mouse moved
            if( event.type == SDL_MOUSEMOTION )
            {
                //Get the mouse offsets
                xb = event.motion.x;
                yb = event.motion.y;

                //If the mouse is over the button
                if( ( xb > 580 ) && ( xb < 580 + hit[0]->w ) && ( yb > 130 ) && ( yb < 130 +hit[0]->h ) )
                {
                    if(!reloadsound)
                    {
                        Mix_PlayChannel( -1, reloading, 0 );
                        Mix_VolumeChunk(reloading, 80);
                        reloadsound = true;

                    }

                    nueva_carga = true;
                }
                else
                    reloadsound = false;


            }

            if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    myTimer.pause();
                    pause();
                    myTimer.unpause();
                }
            }


            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                stagekill = false;
                flagp1 = false;
                flagp2 = false;
                quit = true;
            }

        }
        if(!boss)
         bgX -= 10;
        else
               bgX = 0;

        //If the background has gone too far
        if( bgX <= -background3->w )
        {
            //Reset the offset
            bgX = 0;
        }
      //  SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
         apply_surface( bgX, bgY, background3, screen );
        apply_surface( bgX + background3->w, bgY, background3, screen );
        apply_surface(0,0,layout,screen);
        apply_surface(450,0,lifebar[life],screen);
        if(flagp1)
            apply_surface(450,0,p1icon,screen);
        if(flagp2)
            apply_surface(450,0,p2icon,screen);
        if(gastar==11){
            reloadtext = TTF_RenderText_Blended(fuentegae,"RELOAD",{255,rand()%100+1,0});
            apply_surface(580,130,hit[animate],screen);
            apply_surface(movereloadx,220,reloadtext,screen);
            if(movereloadx!=380)
                movereloadx-=8;
            else
                movereloadx == 380;

            if(frames%80 == 0){
                    Mix_PlayChannel( 1, reloadvoice, 0 );
                    Mix_VolumeChunk(reloadvoice, 80);
            }




            }


        list<Enemies*>::iterator i=enem.begin();
        while(i!=enem.end())
        {

            if((*i)->borrar)
            {
                shoted2 = true;

                if((*i)->tipo=="n")
                {
                    Mix_PlayChannel( 1, miniondead, 0 );
                    Mix_VolumeChunk(miniondead, 100);
                    iz--;
                    if(iz==0)
                        izq= true;
                    if((*i)->powerup)
                    {
                        life=0;
                        pwr[p];

                    }
                    eny+=50;
                    apply_surface((*i)->x,eny,enemy[4],screen);


                }


                if((*i)->tipo=="l")
                {
                    stagekill = true;


                }
    if(frames%50==0){
                s+=100;
                (*i)->where= true;
                Enemies*temp = (*i);
                i = enem.erase(i);
                delete temp;
                eny= 160;
}

            }
              else
            {

               if((*i)->tipo == "l")
                    {
                        if((*i)->y<160){
                        (*i)->mover(true);
                        (*i)->dib(Bsh[0]);
                        }else{
                            (*i)->dib(Bsh[bs]);
                        }
                        if(bs==3&& frames%25==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;

                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);
                                    if(life==8)
                                    {
                                        if(flagp1)
                                            guardarscores(scoreg,"samantha.txt");
                                        else if(flagp2)
                                            guardarscores(scoreg,"mad.txt");
                                        flagp1 = false;
                                        flagp2 = false;
                                        GameOver();
                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }




                    }



                if((*i)->tipo=="n")
                {


                    if(!(*i)->shooting)
                        (*i)->x+=4;
                    if((*i)->morir== 2 && (*i)->powerup)
                    {
                        (*i)->dib(pwup[pw]);
                    }
                    else if((*i)->shooting)
                    {
                    if(!boss)
                        (*i)->x-=8;
                        (*i)->dib(shoot[sh]);
                        if(sh==3 && frames%1==0){
                        Mix_PlayChannel( -1, enemyshot, 0 );
                        Mix_VolumeChunk(enemyshot, 50);
}
                        if(sh==3 && frames%15==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;


                                    if(life==8)
                                    {
                                        if(flagp1)
                                            guardarscores(scoreg,"samantha.txt");
                                        else if(flagp2)
                                            guardarscores(scoreg,"mad.txt");
                                        flagp1 = false;
                                        flagp2 = false;
                                        GameOver();

                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }

                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit1.png"));
                            (*i)-> parp =false;
                        }
                    }
                    else if((*i)->where)
                    {
                        (*i)->dib(enemy[m]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit0.png"));
                            (*i)-> parp =false;
                        }
                    }


                }


                if(frames>5)
                {
                    if((*i)->x>=SCREEN_WIDTH/3 && (*i)->tipo =="n" && frames%40==0)
                        (*i)->shooting =true;

                    (*i)->logica(clickx,clicky);

                }
                if((*i)->x<5 ){

                    iz--;
                    if(iz==0)
                        izq= true;
                Enemies*temp = (*i);
                i = enem.erase(i);
                delete temp;
                }

            }

            i++;
        }




        //Show the button
        myButton.show();
        if(frames%150==0)
        {
            if(ap)
                pw++;
            if(pw>2)
            {
                pw=2;
                ap=false;

            }

            if(c)
                p++;
            if(p>2)
            {
                p=2;
                c= false;
            }


        }
        if(frames%15==0)
        {
            m++;
            sh++;
            n++;
            if(boss)
            bs++;
            if(bossy)
                transport++;
            if(m>1)
                m=0;
            if(sh>3)
                sh=0;
            if(n>1)
                n=0;

            if(transport >7 )
            {
                bossy =false;
                transport=0;
            }
            if(bs>3)
                bs=1;
        }

        if(frames%30)
        {
            if(shotanim < 3)
            {

                shotanim++;
            }

        }
        //Update the screen


        frames++;
        std::stringstream puntaje;
        int actualscore = s;
        puntaje<<"Score : "<<actualscore;
        score= TTF_RenderText_Solid( fuente,puntaje.str().c_str(), {255,255,255} );
        apply_surface(  0, 0, score, screen );
        if(stagekill)
        {



            apply_surface(0,0,stageclear,screen);


                if(flagp1)
                    apply_surface(250,230,p1,screen);
                if(flagp2)
                    apply_surface(240,250,p2,screen);

                                if(life == 0)
                {
                    if(finalscore<500){
                        finalscore+=50;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 500;

                    percent = 100;


                }

                if(life == 1)
                {
                    if(finalscore<400){
                        finalscore+=20;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 400;

                    percent = 80;

                }
                if(life == 2)
                {
                    if(finalscore<300){
                        finalscore+=100;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 300;

                    percent = 60;
                }
                if(life == 3)
                {
                    if(finalscore<200){
                        finalscore+=2;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 200;

                    percent = 45;
                }
                if(life == 4)
                {
                    if(finalscore<100){
                        finalscore+=5;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 100;

                    percent = 30;
                }
                if(life == 5)
                {
                    if(finalscore<50){
                        finalscore+=2;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 50;
                    percent = 20;
                }
                if(life == 6)
                {
                    if(finalscore<25){
                        finalscore+=1;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 25;

                    percent = 10;
                }
                if(life == 7)
                {
                    if(finalscore<10){
                        finalscore++;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 10;


                    percent = 5;
                }








                int totaladd = finalscore+s;
                std::stringstream points;
                std::stringstream lifepoints;

                points<<"Final Score : "<<totaladd;
                lifepoints<<"Health : "<<percent<<"%";
                scoretext= TTF_RenderText_Solid( fuente,points.str().c_str(), {255,255,255} );
                lifetext = TTF_RenderText_Solid( fuente,lifepoints.str().c_str(), {255,255,255} );
                apply_surface(160,150, scoretext, screen );
                apply_surface(160,200,lifetext,screen);


            {
                if(event.key.keysym.sym == SDLK_SPACE)
                {
                                        scoreg+=totaladd;



                            stagekill = false;
                            loadlevel3();


                    }

                }



        }
        if(!boss)
        {
            std::stringstream time;
            if((60 - ((myTimer.get_ticks()-startin)/1000))>=10)
                time <<60 - ((myTimer.get_ticks()-startin)/1000);
            else if((60 - ((myTimer.get_ticks()-startin)/1000))<10)
                time <<"0"<<60 - ((myTimer.get_ticks()-startin)/1000);
            seconds = TTF_RenderText_Solid( fuentegae, time.str().c_str(), textColor );
            apply_surface( 292, 25, seconds, screen );

        }
        if (nueva_carga)
        {
            animgastar1 = 0;
            animgastar2 = 3;
            animgastar3 = 6;
            animgastar4 = 9;
            animgastar5 = 12;
            animgastar6 = 15;
            animgastar7 = 18;
            animgastar8 = 21;
            animgastar9 = 24;
            animgastar10 = 27;
            animgastar11 = 30;
            framegastar = 0;
            gastar = 0;
            apply_surface(530,20, bullet[0], screen);
            nueva_carga=false;
        }


        if (gastar == 0)
        {
            apply_surface(530,20, bullet[0], screen);
        }

        if (gastar == 1 )
        {

            apply_surface(530,20,bullet[animgastar1],screen);
            if (framegastar % 5 == 0)
                animgastar1++;
            framegastar++;

            if(animgastar1 > 3)
            {
                animgastar1 = 3;
            }

        }
        if (gastar == 2)
        {
            apply_surface(530,20,bullet[animgastar2],screen);
            if (framegastar % 5 == 0)
                animgastar2++;
            framegastar++;

            if(animgastar2 > 6)
            {
                animgastar2 = 6;
            }

        }
        if (gastar == 3)
        {
            apply_surface(530,20,bullet[animgastar3],screen);
            if (framegastar % 5 == 0)
                animgastar3++;
            framegastar++;

            if(animgastar3 > 9)
            {
                animgastar3 = 9;
            }

        }
        if (gastar == 4)
        {
            apply_surface(530,20,bullet[animgastar4],screen);
            if (framegastar % 5 == 0)
                animgastar4++;
            framegastar++;

            if(animgastar4 > 12)
            {
                animgastar4 = 12;
            }

        }
        if (gastar == 5)
        {
            apply_surface(530,20,bullet[animgastar5],screen);
            if (framegastar % 5 == 0)
                animgastar5++;
            framegastar++;

            if(animgastar5 > 15)
            {
                animgastar5 = 15;
            }

        }
        if (gastar == 6)
        {
            apply_surface(530,20,bullet[animgastar6],screen);
            if (framegastar % 5 == 0)
                animgastar6++;
            framegastar++;

            if(animgastar6 > 18)
            {
                animgastar6 = 18;
            }

        }
        if (gastar == 7)
        {
            apply_surface(530,20,bullet[animgastar7],screen);
            if (framegastar % 5 == 0)
                animgastar7++;
            framegastar++;

            if(animgastar7 > 21)
            {
                animgastar7 = 21;
            }

        }
        if (gastar == 8)
        {
            apply_surface(530,20,bullet[animgastar8],screen);
            if (framegastar % 5 == 0)
                animgastar8++;
            framegastar++;

            if(animgastar8 > 24)
            {
                animgastar8 = 24;
            }

        }
        if (gastar == 9)
        {
            apply_surface(530,20,bullet[animgastar9],screen);
            if (framegastar % 5 == 0)
                animgastar9++;
            framegastar++;

            if(animgastar9 > 27)
            {
                animgastar9 = 27;
            }

        }
        if (gastar == 10)
        {
            apply_surface(530,20,bullet[animgastar10],screen);
            if (framegastar % 5 == 0)
                animgastar10++;
            framegastar++;

            if(animgastar10 > 30)
            {
                animgastar10 = 30;
            }

        }
        if (gastar == 11)
        {
            apply_surface(530,20,bullet[animgastar11],screen);
            if (framegastar % 5== 0)
                animgastar11++;
            framegastar++;

            if(animgastar11 > 32)
            {
                animgastar11 = 32;
            }

        }


        if(((myTimer.get_ticks()-startin)/1000)==60)
        {
            boss = true;
            bossy =true;
            //quit = true;
        }





        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

        //Fill the screen white




    }








}

void juego()
{

    int gastar = 0;
    bool nueva_carga = false;
    int reload = 33;
    SDL_Surface *bullet[32];
    int framegastar = 0;
    int finalscore = 0;

    bullet[0] = load_image("bullet0.png");
    bullet[1] = load_image("bullet1.png");
    bullet[2] = load_image("bullet2.png");
    bullet[3] = load_image("bullet3.png");
    bullet[4] = load_image("bullet4.png");
    bullet[5] = load_image("bullet5.png");
    bullet[6] = load_image("bullet6.png");
    bullet[7] = load_image("bullet7.png");
    bullet[8] = load_image("bullet8.png");
    bullet[9] = load_image("bullet9.png");
    bullet[10] = load_image("bullet10.png");
    bullet[11] = load_image("bullet11.png");
    bullet[12] = load_image("bullet12.png");
    bullet[13] = load_image("bullet13.png");
    bullet[14] = load_image("bullet14.png");
    bullet[15] = load_image("bullet15.png");
    bullet[16] = load_image("bullet16.png");
    bullet[17] = load_image("bullet17.png");
    bullet[18] = load_image("bullet18.png");
    bullet[19] = load_image("bullet19.png");
    bullet[20] = load_image("bullet20.png");
    bullet[21] = load_image("bullet21.png");
    bullet[22] = load_image("bullet22.png");
    bullet[23] = load_image("bullet23.png");
    bullet[24] = load_image("bullet24.png");
    bullet[25] = load_image("bullet25.png");
    bullet[26] = load_image("bullet26.png");
    bullet[27] = load_image("bullet27.png");
    bullet[28] = load_image("bullet28.png");
    bullet[29] = load_image("bullet29.png");
    bullet[30] = load_image("bullet30.png");
    bullet[31] = load_image("bullet31.png");

    int animgastar1 = 0;
    int animgastar2 = 3;
    int animgastar3 = 6;
    int animgastar4 = 9;
    int animgastar5 = 12;
    int animgastar6 = 15;
    int animgastar7 = 18;
    int animgastar8 = 21;
    int animgastar9 = 25;
    int animgastar10 = 28;
    int animgastar11 = 31;

    SDL_ShowCursor(0);
    SDL_Surface*enemy[5];
    enemy[0]= load_image("running0.png");
    enemy[1]= load_image("running1.png");
    enemy[2]=load_image("enemyhit0.png");
    enemy[3]=load_image("enemyhit1.png");
    enemy[4]=load_image("dead0.png");


    SDL_Surface *en[2];
    en[0]= load_image("running2.png");
    en[1]= load_image("running3.png");

    SDL_Surface *shoot[4];
    shoot[0]= load_image("enemies0.png");
    shoot[1]= load_image("enemies1.png");
    shoot[2]= load_image("enemies2.png");
    shoot[3]= load_image("enemies3.png");

    SDL_Surface * Bt[8];
    Bt[0] = load_image("transport0.png");
    Bt[1] = load_image("transport1.png");
    Bt[2] = load_image("transport2.png");
    Bt[3] = load_image("transport3.png");
    Bt[4] = load_image("transport4.png");
    Bt[5] = load_image("transport5.png");
    Bt[6] = load_image("transport6.png");
    Bt[7] = load_image("transport7.png");

    SDL_Surface * Bsh[7];
    Bsh[0] = load_image("bosshot0.png");
    Bsh[1] = load_image("bosshot1.png");
    Bsh[2] = load_image("bosshot2.png");
    Bsh[3] = load_image("bosshot3.png");
    Bsh[4] = load_image("bosshot4.png");
    Bsh[5] = load_image("bosshot5.png");
    Bsh[6] = load_image("bosshot6.png");
    //Quit flag

    SDL_Surface *lifebar[9];
    lifebar[0] = load_image("lifebar0.png");
    lifebar[1] = load_image("lifebar1.png");
    lifebar[2] = load_image("lifebar2.png");
    lifebar[3] = load_image("lifebar3.png");
    lifebar[4] = load_image("lifebar4.png");
    lifebar[5] = load_image("lifebar5.png");
    lifebar[6] = load_image("lifebar6.png");
    lifebar[7] = load_image("lifebar7.png");
    lifebar[8] = load_image("lifebar8.png");


    SDL_Surface *pwup[3];
    pwup[0] = load_image("health0.png");
    pwup[1] = load_image("health1.png");
    pwup[2] = load_image("health3.png");

    SDL_Surface *pwr[3];
    pwr[0] = load_image("health4.png");
    pwr[1] = load_image("health5.png");
    pwr[2] = load_image("health6.png");

    bool quit = false;


    int life =0;
    srand(time(NULL));
    //Make the button
    Button myButton(120,120,277,229);
    int frames=0;
    list<Enemies*>enem;
    bool izq= true;
    bool der = true;
    bool paused = false;
    bool reloadsound = false;
    bool activatereload = false;
    bool stopsound = false;
    Uint32 startin =0;
    Timer fps;
    int shotanim = 0;
    int boss = false;
    int m=0;
    int percent = 0;
    int sh =0;
    int n=0;
    int d=0;
    int iz=0;
    int transport =0;
    int bs =0;
    int animate = 0;
    bool bossy= false;
    Timer myTimer;
    myTimer.start();
    bool appear = false;
    bool flagizq = false;
    bool flagder = false;
    int s=0;
    bool up = true;
    int pw=0;
    bool ap = false;
    bool b=true;
    SDL_Surface *hit[2];
    hit[0]= load_image("hitit.png");
    hit[1]= load_image("hitit2.png");
    int p =0;
    bool c = false;


    while( quit == false )
    {
        if(Mix_PlayingMusic() == 0){
            Mix_PlayMusic(stage1,-1);
            Mix_VolumeMusic(60);
        }

        paused = true;
        fps.start();


        if(frames%10 == 0)
        {

            animate++;
            if(animate>1)
                animate = 0;


        }

        if(bossy)
        {
            if(b)
            {
                if(!stagekill)
                {

                    enem.push_back((new BOSS(SCREEN_WIDTH/2,240,screen,Bt[0])));
                    b = false;
                }
            }
        }
        if(frames%377 == 0 && izq)
        {
            if(!stagekill)
            {

                if(!flagizq)
                    enem.push_back(new Enemies(0,360,screen,enemy[0],false));
                else
                    enem.push_back(new Enemies(0,350,screen,enemy[0],false));

            }
            flagizq=!flagizq;
            if(iz==2)
            {

                izq=false;

            }

            iz++;
        }
        if(frames%677==0 && der)
        {
            if(!stagekill)
            {

                if(!flagder)
                    enem.push_back(new derecha(560,340,screen,en[0],false));
                else
                    enem.push_back(new derecha(560,330,screen,en[0],false));

            }
            flagder =!flagder;
            d++;
            if(!boss)
            {
                if(d==2 )
                    der=false;
            }
            else if(boss)
            {
                if(d==1 )
                    der=false;
            }
        }
        if(bossy)
        {
            if(up)
            {
                if(!stagekill)
                {

                    enem.push_back(new Enemies(0,360,screen,enemy[0],true));
                    up = false;
                    ap = true;
                    c = true;
                }
            }


        }


        int clickx =-1;
        int clicky= -1;
        int xb = 0, yb = 0;
        while( SDL_PollEvent( &event ) )
        {
            //Handle button events
            myButton.handle_events();
            if(!stagekill)
            {
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (gastar <= 10)
                    {
                        if(event.button.button == SDL_BUTTON_LEFT)
                        {
                            Mix_PlayChannel( -1, firing, 0 );
                            Mix_VolumeChunk(firing, 50);
                            clickx = event.button.x;
                            clicky = event.button.y;
                            shoted = true;
                            frameshot = 0;
                            gastar++;
                            animgastar1 = 0;
                            animgastar2 = 3;
                            animgastar3 = 6;
                            animgastar4 = 9;
                            animgastar5 = 12;
                            animgastar6 = 15;
                            animgastar7 = 18;
                            animgastar8 = 21;
                            animgastar9 = 24;
                            animgastar10 = 27;
                            animgastar11 = 30;
                            framegastar = 0;
                            if (gastar > 32)
                                gastar = 32;

                        }
                    }
                }

            }


            //If the mouse moved
            if( event.type == SDL_MOUSEMOTION )
            {
                //Get the mouse offsets
                xb = event.motion.x;
                yb = event.motion.y;

                //If the mouse is over the button
                if( ( xb > 580 ) && ( xb < 580 + hit[0]->w ) && ( yb > 130 ) && ( yb < 130 +hit[0]->h ) )
                {
                    if(!reloadsound)
                    {
                        Mix_PlayChannel( -1, reloading, 0 );
                        Mix_VolumeChunk(reloading, 80);
                        reloadsound = true;

                    }

                    nueva_carga = true;
                }
                else
                    reloadsound = false;


            }

            if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    myTimer.pause();
                    pause();
                    myTimer.unpause();
                }
            }


            //If the user has Xed out the window
            if( event.type == SDL_QUIT )
            {
                //Quit the program
                stagekill = false;
                flagp1 = false;
                flagp2 = false;
                quit = true;
            }

        }
        SDL_FillRect( screen, &screen->clip_rect, SDL_MapRGB( screen->format, 0xFF, 0xFF, 0xFF ) );
        apply_surface(0,0,background,screen);
        apply_surface(0,0,layout,screen);
        apply_surface(450,0,lifebar[life],screen);
        if(flagp1)
            apply_surface(450,0,p1icon,screen);
        if(flagp2)
            apply_surface(450,0,p2icon,screen);

        if(gastar==11){
            reloadtext = TTF_RenderText_Blended(fuentegae,"RELOAD",{255,rand()%100+1,0});
            apply_surface(580,130,hit[animate],screen);
            apply_surface(movereloadx,220,reloadtext,screen);
            if(movereloadx!=380)
                movereloadx-=8;
            else
                movereloadx == 380;

            if(frames%80 == 0){
                    Mix_PlayChannel( 1, reloadvoice, 0 );
                    Mix_VolumeChunk(reloadvoice, 80);
            }


            }



            if(nueva_carga)
                movereloadx = 620;



        list<Enemies*>::iterator i=enem.begin();
        while(i!=enem.end())
        {

            if((*i)->borrar)
            {
                shoted2 = true;
                s+=100;
                if((*i)->tipo=="n")
                {
                    Mix_PlayChannel( 1, miniondead, 0 );
                    Mix_VolumeChunk(miniondead, 100);
                    iz--;
                    if(iz==0)
                        izq= true;
                    if((*i)->powerup)
                    {
                        life=0;
                        pwr[p];

                    }
                    (*i)->dib(enemy[4]);
                }
                if((*i)->tipo=="d")
                {
                    Mix_PlayChannel( 1, miniondead, 0 );
                    Mix_VolumeChunk(miniondead, 100);
                    d--;
                    if(d==0)
                        der= true;
                    (*i)->dib(enemy[4]);

                }

                if((*i)->tipo=="b")
                {
                    stagekill = true;


                }

                (*i)->where= true;
                Enemies*temp = (*i);
                i = enem.erase(i);


                delete temp;

            }
            else
            {

                if((*i)->tipo == "b" && bossy)
                {
                    (*i)->dib(Bt[transport]);
                    if(!stopsound){
                    Mix_PlayChannel( 1, imgonnakillyou, 0 );
                    Mix_VolumeChunk(imgonnakillyou, 100);
                    stopsound = true;
                    }

                }
                else
                {
                    if((*i)->tipo == "b" && boss)
                    {

                        (*i)->dib(Bsh[bs]);
                        if(bs==6 && frames%15==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;

                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);
                                    if(life==8)
                                    {
                                        flagp1 = false;
                                        flagp2 = false;
                                        GameOver();
                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }

                        if((*i)->morir%15==0)
                        {
                            (*i)->dib(Bt[7]);
                            (*i)->dib(Bt[6]);
                            (*i)->dib(Bt[5]);
                            (*i)->dib(Bt[4]);
                            (*i)->dib(Bt[3]);
                            (*i)->dib(Bt[2]);
                            (*i)->dib(Bt[1]);
                            (*i)->dib(Bt[0]);
                            srand(time(NULL));
                            (*i)->mover(rand()%2);
                            (*i)->morir++;
                            bossy = true;

                        }



                    }
                }


                if((*i)->tipo=="n")
                {


                    if((*i)->where && (*i)->x<=560 )
                    {
                        if((*i)->x==560)
                            (*i)->where = false;
                    }
                    if((*i)->x==0 )
                    {
                        (*i)->where = true;

                    }
                    if(!(*i)->shooting)
                        (*i)->mover((*i)->where);
                    if((*i)->morir== 2 && (*i)->powerup)
                    {
                        (*i)->dib(pwup[pw]);
                    }
                    else if((*i)->shooting)
                    {
                        (*i)->dib(shoot[sh]);
                        if(sh==3 && frames%15==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;

                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);
                                    if(life==8)
                                    {
                                        flagp1 = false;
                                        flagp2 = false;
                                        GameOver();

                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }

                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit1.png"));
                            (*i)-> parp =false;
                        }
                    }
                    else if((*i)->where)
                    {
                        (*i)->dib(enemy[m]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit0.png"));
                            (*i)-> parp =false;
                        }
                    }
                    else
                    {
                        (*i)->dib(en[m]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit3.png"));
                            (*i)-> parp =false;
                        }
                    }

                }
                else if((*i)->tipo == "d")
                {
                    if((*i)->where && (*i)->x>=0 )
                    {
                        if((*i)->x==0)
                            (*i)->where = false;
                    }
                    if((*i)->x>560 )
                    {
                        (*i)->where = true;
                    }
                    if(!(*i)->shooting)
                        (*i)->mover((*i)->where);
                    if((*i)->shooting)
                    {
                        (*i)->dib(shoot[sh]);
                        if(sh==3 && frames%15==0)
                        {
                            if(!stagekill)
                            {
                                if(life<8)
                                {
                                    life+=1;
                                    Mix_PlayChannel( -1, enemyshot, 0 );
                                    Mix_VolumeChunk(enemyshot, 50);

                                    if(life==8)
                                    {
                                        flagp1 = false;
                                        flagp1 = false;
                                        GameOver();
                                    }
                                }
                            }

                        }
                        else if(sh==3)
                        {
                            if(!stagekill)
                                apply_surface(0,0,hurt, screen);
                        }


                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit2.png"));
                            (*i)-> parp =false;
                        }


                    }
                    else if((*i)->where)
                    {
                        (*i)->dib(en[n]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit3.png"));
                            (*i)-> parp =false;
                        }
                    }
                    else
                    {
                        (*i)->dib(enemy[n]);
                        if((*i)->morir ==1 && (*i)->parp)
                        {
                            (*i)->dib(load_image("enemyhit0.png"));
                            (*i)-> parp =false;
                        }
                    }



                }

                if(frames>5)
                {
                    if(frames%255==0 && (*i)->tipo =="n")
                        (*i)->shooting =true;
                    else if(frames%355==0 && (*i)->tipo =="d")
                        (*i)->shooting =true;
                    (*i)->logica(clickx,clicky);

                }

            }

            i++;
        }



        //Show the button
        myButton.show();
        if(frames%150==0)
        {
            if(ap)
                pw++;
            if(pw>2)
            {
                pw=2;
                ap=false;

            }

            if(c)
                p++;
            if(p>2)
            {
                p=2;
                c= false;
            }


        }
        if(frames%15==0)
        {
            m++;
            sh++;
            n++;
            bs++;
            if(bossy)
                transport++;
            if(m>1)
                m=0;
            if(sh>3)
                sh=0;
            if(n>1)
                n=0;

            if(transport >7 )
            {
                bossy =false;
                transport=0;
            }
            if(bs>6)
                bs=0;
        }

        if(frames%30)
        {
            if(shotanim < 3)
            {

                shotanim++;
            }

        }
        //Update the screen


        frames++;
        std::stringstream puntaje;
        int actualscore = s;
        puntaje<<"Score : "<<actualscore;
        score= TTF_RenderText_Solid( fuente,puntaje.str().c_str(), {255,255,255} );
        apply_surface(  0, 0, score, screen );
        if(stagekill)
        {



            apply_surface(0,0,stageclear,screen);


                if(flagp1)
                    apply_surface(250,230,p1,screen);
                if(flagp2)
                    apply_surface(240,250,p2,screen);

                if(life == 0)
                {
                    if(finalscore<500){
                        finalscore+=50;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 500;

                    percent = 100;


                }

                if(life == 1)
                {
                    if(finalscore<400){
                        finalscore+=20;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 400;

                    percent = 80;

                }
                if(life == 2)
                {
                    if(finalscore<300){
                        finalscore+=100;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 300;

                    percent = 60;
                }
                if(life == 3)
                {
                    if(finalscore<200){
                        finalscore+=2;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 200;

                    percent = 45;
                }
                if(life == 4)
                {
                    if(finalscore<100){
                        finalscore+=5;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 100;

                    percent = 30;
                }
                if(life == 5)
                {
                    if(finalscore<50){
                        finalscore+=2;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 50;
                    percent = 20;
                }
                if(life == 6)
                {
                    if(finalscore<25){
                        finalscore+=1;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 25;

                    percent = 10;
                }
                if(life == 7)
                {
                    if(finalscore<10){
                        finalscore++;
                        Mix_PlayChannel( -1, coin, 0 );
                        Mix_VolumeChunk(coin, 70);
                        }
                    else
                        finalscore = 10;


                    percent = 5;
                }





                int totaladd = finalscore+s;
                std::stringstream points;
                std::stringstream lifepoints;

                points<<"Final Score : "<<totaladd;
                lifepoints<<"Health : "<<percent<<"%";
                scoretext= TTF_RenderText_Solid( fuente,points.str().c_str(), {255,255,255} );
                lifetext = TTF_RenderText_Solid( fuente,lifepoints.str().c_str(), {255,255,255} );
                apply_surface(160,150, scoretext, screen );
                apply_surface(160,200,lifetext,screen);
  while(SDL_PollEvent(&event))
        {


               if(event.type == SDL_KEYDOWN )
            {
                if(event.key.keysym.sym == SDLK_SPACE)
                {

                            stagekill = false;
                            scoreg+=totaladd;
                            loadlevel2();
                            return;


                    }

                }


            }


        }
        if(!boss)
        {
            std::stringstream time;
            if((60 - ((myTimer.get_ticks()-startin)/1000))>=10)
                time <<60 - ((myTimer.get_ticks()-startin)/1000);
            else if((60 - ((myTimer.get_ticks()-startin)/1000))<10)
                time <<"0"<<60 - ((myTimer.get_ticks()-startin)/1000);
            seconds = TTF_RenderText_Solid( fuentegae, time.str().c_str(), textColor );
            apply_surface( 292, 25, seconds, screen );

        }
        if (nueva_carga)
        {
            animgastar1 = 0;
            animgastar2 = 3;
            animgastar3 = 6;
            animgastar4 = 9;
            animgastar5 = 12;
            animgastar6 = 15;
            animgastar7 = 18;
            animgastar8 = 21;
            animgastar9 = 24;
            animgastar10 = 27;
            animgastar11 = 30;
            framegastar = 0;
            gastar = 0;
            apply_surface(530,20, bullet[0], screen);
            nueva_carga=false;
        }


        if (gastar == 0)
        {
            apply_surface(530,20, bullet[0], screen);
        }

        if (gastar == 1 )
        {

            apply_surface(530,20,bullet[animgastar1],screen);
            if (framegastar % 5 == 0)
                animgastar1++;
            framegastar++;

            if(animgastar1 > 3)
            {
                animgastar1 = 3;
            }

        }
        if (gastar == 2)
        {
            apply_surface(530,20,bullet[animgastar2],screen);
            if (framegastar % 5 == 0)
                animgastar2++;
            framegastar++;

            if(animgastar2 > 6)
            {
                animgastar2 = 6;
            }

        }
        if (gastar == 3)
        {
            apply_surface(530,20,bullet[animgastar3],screen);
            if (framegastar % 5 == 0)
                animgastar3++;
            framegastar++;

            if(animgastar3 > 9)
            {
                animgastar3 = 9;
            }

        }
        if (gastar == 4)
        {
            apply_surface(530,20,bullet[animgastar4],screen);
            if (framegastar % 5 == 0)
                animgastar4++;
            framegastar++;

            if(animgastar4 > 12)
            {
                animgastar4 = 12;
            }

        }
        if (gastar == 5)
        {
            apply_surface(530,20,bullet[animgastar5],screen);
            if (framegastar % 5 == 0)
                animgastar5++;
            framegastar++;

            if(animgastar5 > 15)
            {
                animgastar5 = 15;
            }

        }
        if (gastar == 6)
        {
            apply_surface(530,20,bullet[animgastar6],screen);
            if (framegastar % 5 == 0)
                animgastar6++;
            framegastar++;

            if(animgastar6 > 18)
            {
                animgastar6 = 18;
            }

        }
        if (gastar == 7)
        {
            apply_surface(530,20,bullet[animgastar7],screen);
            if (framegastar % 5 == 0)
                animgastar7++;
            framegastar++;

            if(animgastar7 > 21)
            {
                animgastar7 = 21;
            }

        }
        if (gastar == 8)
        {
            apply_surface(530,20,bullet[animgastar8],screen);
            if (framegastar % 5 == 0)
                animgastar8++;
            framegastar++;

            if(animgastar8 > 24)
            {
                animgastar8 = 24;
            }

        }
        if (gastar == 9)
        {
            apply_surface(530,20,bullet[animgastar9],screen);
            if (framegastar % 5 == 0)
                animgastar9++;
            framegastar++;

            if(animgastar9 > 27)
            {
                animgastar9 = 27;
            }

        }
        if (gastar == 10)
        {
            apply_surface(530,20,bullet[animgastar10],screen);
            if (framegastar % 5 == 0)
                animgastar10++;
            framegastar++;

            if(animgastar10 > 30)
            {
                animgastar10 = 30;
            }

        }
        if (gastar == 11)
        {
            apply_surface(530,20,bullet[animgastar11],screen);
            if (framegastar % 5== 0)
                animgastar11++;
            framegastar++;

            if(animgastar11 > 32)
            {
                animgastar11 = 32;
            }

        }


        if(((myTimer.get_ticks()-startin)/1000)==60)
        {
            boss = true;
            bossy =true;
            //quit = true;
        }





        if( SDL_Flip( screen ) == -1 )
        {
            return ;
        }
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

        //Fill the screen white




    }



}

void characterselect()
{
    SDL_SetCursor(0);

    int frame = 0;
    int bgx =0;
    int bgy = 0;
    int i = 0;
    int selecting = 1;
    int randomcolor1 = 0;
    int randomcolor2 = 0;
    int randomcolor3 = 0;
    bool cap = true;
    Timer fps;
    int alphavalue = SDL_ALPHA_OPAQUE;
    SDL_Surface*entertext = NULL;
    SDL_Surface*selectplayer = load_image("selectplayer.png");

    int movex = 0;
    int movey = 0;
    bool quit = false;

    SDL_Surface* animation[3];
    animation[0] = load_image("characteranim0.png");
    animation[1] = load_image("characteranim1.png");
    animation[2] = load_image("characteranim2.png");



    while(quit == false)
    {
        SDL_ShowCursor(0);

        if( alphavalue > SDL_ALPHA_TRANSPARENT )
        {
            //Decrease alpha
            alphavalue -= 10;
        }

        while(SDL_PollEvent(&event))
        {

            if(flagp1== true || flagp2 == true)
            {

                if(event.type == SDL_MOUSEBUTTONDOWN)
                {

                    if(event.button.button == SDL_BUTTON_LEFT)
                    {

                        loadlevel1();
                        return;


                    }

                }

            }

            if(event.type == SDL_KEYDOWN )
            {

                if(!flagp2)
                {
                    if(event.key.keysym.sym == SDLK_LEFT)
                    {
                        Mix_PlayChannel( -1, slect, 0 );
                        Mix_VolumeChunk(slect, 50);
                        if(selecting>1)
                        {
                            selecting--;
                            break;
                        }
                    }
                }

                if(!flagp1)
                {
                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        Mix_PlayChannel( -1, slect, 0 );
                        Mix_VolumeChunk(slect, 50);
                        if(selecting<2)
                        {
                            selecting++;
                            break;
                        }
                    }
                }


                if(event.key.keysym.sym == SDLK_RETURN)
                {

                    if(selecting == 1)
                    {

                        flagp1 = true;

                    }

                    if(selecting == 2)
                    {
                        flagp2 = true;

                    }



                }



                if(event.key.keysym.sym == SDLK_BACKSPACE)
                {

                    if(selecting == 1)
                    {

                        flagp1 = false;
                    }

                    if(selecting == 2)
                    {
                        flagp2 = false;
                    }

                }



            }

        }



        bgx -= 5;


        randomcolor1+=20;

        randomcolor3+=20;

        if(flagp1)
        {

            samantha = TTF_RenderText_Blended(fuentegae,"SAMANTHA", {255,255,255});

        }
        if(flagp2)
        {
            mad = TTF_RenderText_Blended(fuentegae,"MAD", {255,255,255});
        }

        if(flagp1==true || flagp2==true)
        {

            entertext = TTF_RenderText_Blended(fuente,"PRESS FIRE BUTTON TO START", {0,randomcolor3,255});

        }
        if(randomcolor1 == 120)
        {
            randomcolor1=0;
        }
        if(randomcolor2 == 180)
        {


            randomcolor2 = 0;
        }
        if(randomcolor3 == 255)
        {

            randomcolor3 = 0;
        }



        if(i%2 == 0)
        {

            if(frame<2)
            {
                frame++;
            }



        }

        if(bgx <= -scroll->w)
        {

            bgx =0;
        }



        apply_surface(bgx,bgy,scroll,screen);
        apply_surface(bgx + scroll->w,bgy,scroll,screen);
        apply_surface(0,0,animation[frame], screen);

        if(frame == 2)
        {
            apply_surface(0,-25,selectplayer,screen);
            apply_surface(110,80,p1,screen);
            apply_surface(400, 104,p2,screen);
            apply_surface(50,300,samantha,screen);
            apply_surface(450 , 300,mad, screen);
            if(flagp1 == true || flagp2 == true)
                apply_surface(110,380,entertext,screen);
        }

        if(selecting == 1)
        {
            samantha = TTF_RenderText_Blended(fuentegae,"SAMANTHA", {randomcolor1,randomcolor2,randomcolor3});
            apply_surface(18,300,guntip,screen);


        }
        else
            samantha = TTF_RenderText_Blended(fuentegae,"SAMANTHA", {0,0,0});
        if(selecting == 2)
        {
            mad = TTF_RenderText_Blended(fuentegae,"MAD", {randomcolor1,randomcolor2,randomcolor3});
            apply_surface(420,300,guntip,screen);
        }
        else
            mad = TTF_RenderText_Blended(fuentegae,"MAD", {0,0,0});





        if(SDL_Flip(screen) == -1)
        {

            return;
        }


        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        i++;





    }

}

void opciones(){
    int frame = 0;
    bool cap = true;
    Timer fps;
    SDL_Surface* msj = NULL;
    SDL_Surface* y = NULL;
    SDL_Surface* n = NULL;
    SDL_Surface* nothing = load_image("null.png");

    int movex = 0;
    int movey = 0;
    bool quit = false;
    int selecting = 1;

    while(quit == false)
    {

        msj = TTF_RenderText_Solid(fuente, "FULLSCREEN?:", {255,255,255});
        y = TTF_RenderText_Solid(fuente, "YES", {255,255,255});
        n = TTF_RenderText_Solid(fuente, "NO", {255,255,255});
        fps.start();
        cap = ( !cap );



        apply_surface(0,0,nothing,screen);
        apply_surface(240,100, msj,screen);

        while(SDL_PollEvent(&event))
            {
        if(event.type == SDL_KEYDOWN )
            {


                    if(event.key.keysym.sym == SDLK_LEFT)
                    {
                        Mix_PlayChannel( -1, slect, 0 );
                        Mix_VolumeChunk(slect, 50);

                        if(selecting>1)
                        {
                            selecting--;
                            break;
                        }
                    }



                    if(event.key.keysym.sym == SDLK_RIGHT)
                    {
                        Mix_PlayChannel( -1, slect, 0 );
                        Mix_VolumeChunk(slect, 50);

                        if(selecting<2)
                        {
                            selecting++;
                            break;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_RETURN){
                        if(selecting == 1)
                            screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE | SDL_FULLSCREEN );

                        if(selecting == 2)
                             screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
                    }

                    if(event.key.keysym.sym == SDLK_BACKSPACE || event.key.keysym.sym == SDLK_ESCAPE){
                        return;
                    }
                }







        }
          if(selecting == 1)
                    apply_surface(307,220, y,screen);
                    else
                    apply_surface(307,220, n,screen);


        frame++;

        if(SDL_Flip(screen) == -1)
        {

            return;
        }
        ;

        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

    }


}

void displayreverse();
void MadnessMenu()
{
    int frame = 0;
    int i = 0;
    int alphavalue = SDL_ALPHA_OPAQUE;
    bool cap = true;
    Timer fps;
    int menux = 0;
    int menuy = 0;
    int groundx = 0;
    int groundy = 0;
    int movex = 0;
    int movey = -518;
    bool quit = false;
    int selecting = 1;
    bool fullscreen = false;
    SDL_Surface* snow[9];
    SDL_Surface* snows[5];
    SDL_Surface* logo[4];

    bool pressed =false;
    bool appear = false;

    snow[0] = load_image("snow0.png");
    snow[1] = load_image("snow1.png");
    snow[2] = load_image("snow2.png");
    snow[3] = load_image("snow3.png");
    snow[4] = load_image("snow4.png");
    snow[5] = load_image("snow5.png");
    snow[6] = load_image("snow6.png");
    snow[7] = load_image("snow7.png");
    snow[8] = load_image("snow8.png");
    logo[0] = load_image("logo0.png");
    logo[1] = load_image("logo1.png");
    logo[2] = load_image("logo2.png");
    logo[3] = load_image("logo3.png");
    snows[0] = load_image("snow9.png");
    snows[1] = load_image("snow10.png");
    snows[2] = load_image("snow11.png");
    snows[3] = load_image("snow12.png");
    snows[4] = load_image("snow13.png");

    press = TTF_RenderText_Solid(font, "PRESS ENTER TO START", textColorc);




    while(quit == false)
    {
        Mix_HaltMusic();
        fps.start();
        cap = ( !cap );

        while(SDL_PollEvent(&event))
        {

            if(event.type == SDL_QUIT)
            {


                exit(0);
            }



            if(event.type == SDL_KEYDOWN )
            {



                if(!pressed)
                {
                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
                        pressed = true;

                        menux = 1;

                        if(menux<2)
                        {
                            menux=2;
                            pressed = false;

                        }


                    }

                }

            }

        }




        if(SDL_Flip(screen) == -1)
        {

            return;
        }


        apply_surface(0,0,background1,screen);
        apply_surface(0,0,snow[frame], screen);
        apply_surface(0,0,snows[movex], screen);
        apply_surface(0,0,logo[groundx], screen);






        if(menux!= 0)
        {
            apply_surface(0,0,slides[menuy], screen);
            if(i%6 == 0)
            {
                if(menuy<2)
                {
                    menuy++;
                }
            }

        }
        if(menuy == 2)
        {
            apply_surface(240,280,play1,screen);
            apply_surface(240,310,play2,screen);
            apply_surface(240,340,options,screen);
            apply_surface(240,370,salir,screen);



                if(event.type != SDL_KEYDOWN && event.type!= SDL_MOUSEBUTTONDOWN){
                    if(i%600 == 0)
                        displayreverse();
                    }




            if(selecting == 1)
            {

                apply_surface(205, 280, guntip, screen);
                play1 = TTF_RenderText_Solid(fuente, "Single Player", {0,0,0});

            }
            else
                play1 = TTF_RenderText_Solid(fuente, "Single Player", textColorc);

            if(selecting == 2)
            {
                apply_surface(205, 310, guntip, screen);
                play2 = TTF_RenderText_Solid(fuente ,"Multiplayer", {0,0,0});

            }
            else
                play2 = TTF_RenderText_Solid(fuente ,"Multiplayer", textColorc);

            if(selecting == 3)
            {

                apply_surface(205, 340, guntip, screen);
                options = TTF_RenderText_Solid(fuente, "Options", {0,0,0});


            }
            else
                options = TTF_RenderText_Solid(fuente, "Options", textColorc);

            if(selecting == 4)
            {
                apply_surface(205, 370, guntip, screen);
                salir = TTF_RenderText_Solid(fuente, "Exit", {0,0,0});


            }
            else
                salir = TTF_RenderText_Solid(fuente, "Exit", textColorc);



            while(SDL_PollEvent(&event))
            {
                if(event.type == SDL_KEYDOWN )
                {


                    if(event.key.keysym.sym == SDLK_RETURN)
                    {
//                            Mix_PlayChannel( -1, entergun, 0 );
//                            Mix_VolumeChunk(entergun, 50);

                        if(selecting == 1)
                        {



                            characterselect();

                        }
                        if(selecting == 2)
                        {

                        }
                        if(selecting == 3)
                        {
                            opciones();


                        }


                        if(selecting == 4)
                        {
                            screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
                            exit(0);
                        }
                    }
                    if(event.key.keysym.sym == SDLK_UP)
                    {
                        Mix_PlayChannel( -1, slect, 0 );
                        Mix_VolumeChunk(slect, 50);

                        if(selecting>1)
                        {
                            selecting--;
                            break;
                        }
                    }

                    if(event.key.keysym.sym == SDLK_DOWN)
                    {
                        Mix_PlayChannel( -1, slect, 0 );
                        Mix_VolumeChunk(slect, 50);
                        if(selecting<4)
                        {
                            selecting++;
                            break;
                        }
                    }
                }
            }

        }

        if(menux == 0)
        {

            apply_surface(125,300,press,screen);
        }





        {
            frame++;
            if(i%10 == 0)
                movex++;

            if(frame >9)
            {
                frame = 8;

            }
            if(movex>4)
            {
                movex = 0;
            }



        }

        if(i%20 == 0)
        {

            if(groundx<3)
            {
                Mix_PlayChannel( -1, entergun, 0 );
                Mix_VolumeChunk(entergun, 55);

                apply_surface(0,0,delay, screen);
                groundx++;

            }





        }





        i++;


        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
    }



}

void display()
{
    int frame = 0;
    bool cap = true;
    Timer fps;
    SDL_Surface* msj = NULL;

    int movex = 0;
    int movey = 0;
    bool quit = false;
    int selecting = 1;

    while(quit == false)
    {

        msj = TTF_RenderText_Solid(fuente, "CHIPNOSE PRESENTS:", {204,255,229});
        fps.start();
        cap = ( !cap );


        apply_surface(0,movey,back, screen);
        apply_surface(180,200,msj, screen);



        frame++;
        movey-=2;
        if(movey == -520)
        {
            MadnessMenu();

        }
        if(SDL_Flip(screen) == -1)
        {

            return;
        }
        ;

        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

    }

}

void displayreverse()
{
    int frame = 0;
    int y= 420;
    bool cap = true;
    Timer fps;
    SDL_Surface* msj = NULL;
    int eny = 400;
    int movex = 0;
    int movey = -520;
    bool quit = false;
    int selecting = 1;
 SDL_Surface* nums1 = NULL;
        SDL_Surface* nums2 = NULL;
        SDL_Surface* nums3 = NULL;
        SDL_Surface* nums4 = NULL;
        SDL_Surface* nums5 = NULL;
        SDL_Surface* nums6 = NULL;

          std::stringstream highscore1;
        std::stringstream highscore2;
        std::stringstream highscore3;
          std::stringstream highscore4;
        std::stringstream highscore5;
        std::stringstream highscore6;

        int h1=0;
        int h2=0;
        int h3=0;
        int h4=0;
        int h5=0;
        int h6=0;

    ifstream getting("mad.txt");
    getting>>h1>>h2>>h3;
    getting.close();
    highscore1<<h1;
    highscore2<<h2;
    highscore3<<h3;
    ifstream get("samantha.txt");
    get>>h4>>h5>>h6;
    getting.close();
     highscore4<<h4;
    highscore5<<h5;
    highscore6<<h6;
    while(quit == false)
    {


        nums1 = TTF_RenderText_Solid(fuentegae, highscore1.str().c_str(), {0,255,255});
        nums2 = TTF_RenderText_Solid(fuentegae, highscore2.str().c_str(), {0,255,255});
        nums3 = TTF_RenderText_Solid(fuentegae, highscore3.str().c_str(), {0,255,255});
         nums4 = TTF_RenderText_Solid(fuentegae, highscore4.str().c_str(), {0,255,255});
        nums5 = TTF_RenderText_Solid(fuentegae, highscore5.str().c_str(), {0,255,255});
        nums6 = TTF_RenderText_Solid(fuentegae, highscore6.str().c_str(), {0,255,255});


        msj = TTF_RenderText_Solid(loadl, "Top Ranking:", {rand()%100+1,0,0});
        fps.start();
        cap = ( !cap );


        apply_surface(0,movey,back, screen);
        apply_surface(100,eny,msj, screen);
        apply_surface(0,y,scr,screen);
        apply_surface(150,y+150,p2icon,screen);
        apply_surface(200, y+150, nums1,screen);
        apply_surface(150,y+220,p2icon,screen);
        apply_surface(200,y+220, nums2,screen);
        apply_surface(150,y+290,p2icon,screen);
        apply_surface(200, y+290, nums3,screen);

        apply_surface(350,y+150,p1icon,screen);
        apply_surface(400, y+150, nums4,screen);
        apply_surface(350,y+220,p1icon,screen);
        apply_surface(400,y+220, nums5,screen);
        apply_surface(350,y+290,p1icon,screen);
        apply_surface(400, y+290, nums6,screen);

        frame++;
        if(eny>0)
            eny--;
        if(movey<=0)
        movey+=2;
        if(y>0)
            y--;

        if(frame%800 == 0)
            display();

        if(SDL_Flip(screen) == -1)
        {

            return;
        }
        ;

        if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) )
        {
            //Sleep the?.d remaining frame time
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }

    }

}

void fade()
{

    int frame = 0;
    bool cap = true;
    Timer fps;

    int alphavalue = SDL_ALPHA_OPAQUE;
    int movex = 0;
    int movey = 0;
    bool quit = false;


    while(quit == false)
    {

        if( alphavalue > SDL_ALPHA_TRANSPARENT )
        {
            //Decrease alpha
            alphavalue -= 5;
        }


        SDL_SetAlpha(front,SDL_SRCALPHA,alphavalue);
        apply_surface(0,0,back,screen);
        apply_surface(0,0,front,screen);

        if(alphavalue == SDL_ALPHA_TRANSPARENT)
            display();


        if(SDL_Flip(screen) == -1)
        {

            return;
        }
        ;

        if( ( cap == true ) && ( fps.get_ticks() < 1000 / 40 ) )
        {
            //Sleep the remaining frame time
            SDL_Delay( ( 1000 / 40 ) - fps.get_ticks() );
        }

    }

}

int frameaux = 0;
void Button::show()
{
    //Show the button
    if(frameshot>=4)
    {
        shoted = false;


    }
    if(frameshot2>=1)
    {

        shoted2 = false;
    }


    if(!shoted)
        apply_surface( box.x, box.y, buttonSheet, screen,NULL );
    else
        apply_surface((event.button.x)-50,(event.button.y)-50, shots[frameshot], screen);

    if(frameaux%4 == 0)
    {
        frameshot++;
        frameshot2++;
    }

    frameaux++;
}
int main( int argc, char* args[] )
{
    bool cap = true;
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }


    //Load the files
    if( load_files() == false )
    {
        return 1;
    }

    rellenar();

    fade();



    clean_up();

    return 0;
}
