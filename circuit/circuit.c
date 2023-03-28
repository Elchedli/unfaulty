/**
* @file circuit.c
* @brief il y a ici tous les fonctions de  l'enigme.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_events.h"
#include "/usr/include/SDL/SDL_mouse.h"
#include "circuit.h"

int hover(SDL_Rect pos,int x,int y){
    Uint8 p;
    if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
    else return 0;
}
/**
* @brief initialiser les donnees de l'enigme.
* @param simple *screen,*locked,*image : adresse pour changer avec surface et position de l'ecran,disponibilité et le background.
* @param protocol base3[],base2[] : different protocols pour liaison du circuit avec position et surface.
* @param SDL_Surface* pos3[],pos2[] : images des differents positions du protocol.
* @return Initialisation de l'enigme
*/
void initialiser(simple *screen,protocol base3[],protocol base2[],SDL_Surface* pos3[],SDL_Surface* pos2[],SDL_Surface* *unlocked,SDL_Surface* *lockked,simple *circuit,simple *locked,simple *image){
	image->image = IMG_Load("/home/shidono/Desktop/circuit/background.png");
    screen->image = SDL_SetVideoMode(1000, 550, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    circuit->image = IMG_Load("/home/shidono/Desktop/circuit/plan.png");
    (*unlocked) = IMG_Load("/home/shidono/Desktop/circuit/unlocked.png");
    (*lockked) = IMG_Load("/home/shidono/Desktop/circuit/locked.png");
    pos3[0] = IMG_Load("/home/shidono/Desktop/circuit/3pos1.png");
    pos3[1] = IMG_Load("/home/shidono/Desktop/circuit/3pos2.png");
    pos3[2] = IMG_Load("/home/shidono/Desktop/circuit/3pos3.png");
    pos3[3] = IMG_Load("/home/shidono/Desktop/circuit/3pos4.png");
    pos2[0] = IMG_Load("/home/shidono/Desktop/circuit/2pos1.png");
    pos2[1] = IMG_Load("/home/shidono/Desktop/circuit/2pos2.png");
    locked->image = (*lockked);

    base3[0].image = pos3[0];
    base3[1].image = pos3[2];
    base3[2].image = pos3[0];
    base2[0].image = pos2[1];
    base2[1].image = pos2[1];


	base3[0].direction = 3;
    base3[1].direction = 2;
    base3[2].direction = 1;
    base2[0].direction = 0;
    base2[1].direction = 1;

    image->pos.x = 0;
    image->pos.y = 0;

    screen->pos.x = 0;
    screen->pos.y = 0;
    screen->pos.w = image->image->w;
    screen->pos.h = image->image->h;

    circuit->pos.x = 0;
    circuit->pos.y = 0;

    base3[0].pos.x = 58;
    base3[0].pos.y = 181;

    base3[1].pos.x = 290;
    base3[1].pos.y = 180;

    base3[2].pos.x = 495;
    base3[2].pos.y = 247;

    base2[0].pos.x = 241;
    base2[0].pos.y = 322;

    base2[1].pos.x = 670;
    base2[1].pos.y = 256;

    locked->pos.x = 863;
    locked->pos.y = 282;
}
/**
* @brief afficher et modifier les donnees de l'enigme.
* @param simple screen : affiche l'ecran.
* @param protocol base3[],base2[] : change surface des liaisons electriques.
* @param SDL_Surface pos3[],pos2[]: les differents liaisons qu'il faut prendre et changer dans le circuit.
* @param SDL_Event event : fait les actions generer pas le hardware.
* @param simple circuit : affiche la base circuit avec sa position.
* @return affichage de l'enigme.
*/
void afficher(simple screen, protocol base3[], protocol base2[], SDL_Surface* pos3[], SDL_Surface* pos2[], SDL_Surface* unlocked, SDL_Surface* lockked,simple circuit, simple *locked, SDL_Event event, simple image){
	int done = 1,x = 0,y = 0,a = 0,b = 0,c = 0;

	SDL_BlitSurface(image.image,NULL,screen.image,&image.pos);
    SDL_BlitSurface(circuit.image,NULL,screen.image,&circuit.pos);
    SDL_BlitSurface(locked->image,NULL,screen.image,&locked->pos);
    SDL_BlitSurface(base3[0].image,NULL,screen.image,&base3[0].pos);
    SDL_BlitSurface(base3[1].image,NULL,screen.image,&base3[1].pos);
    SDL_BlitSurface(base3[2].image,NULL,screen.image,&base3[2].pos);
    SDL_BlitSurface(base2[0].image,NULL,screen.image,&base3[0].pos);
    SDL_BlitSurface(base2[1].image,NULL,screen.image,&base2[1].pos);
    SDL_Flip(screen.image);
    while(done){

        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    a = hover(base3[0].pos,x,y);
                    b = hover(base3[1].pos,x,y);
                    c = hover(base3[2].pos,x,y);
                    if(( a || b || c) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        if(a){
                            if(base3[0].direction == 3){
                                base3[0].direction = 0;
                                base3[0].image = pos3[0];
                            }else{
                                base3[0].direction++;
                                base3[0].image = pos3[base3[0].direction];
                            }
                        }else if(b){
                            if(base3[1].direction == 3){
                                base3[1].direction = 0;
                                base3[1].image = pos3[0];
                            }else{
                                base3[1].direction++;
                                base3[1].image = pos3[base3[1].direction];
                            }
                        }else if(c){
                            if(base3[2].direction == 3){
                                base3[2].direction = 0;
                                base3[2].image = pos3[0];
                            }else{
                                base3[2].direction++;
                                base3[2].image = pos3[base3[2].direction];
                            }
                        }
                    }else if((hover(base2[0].pos,x,y) || hover(base2[1].pos,x,y)) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        if(hover(base2[0].pos,x,y)){
                            if(base2[0].direction == 1){
                                base2[0].direction = 0;
                                base2[0].image = pos2[0];
                            }else{
                                base2[0].direction = 1;
                                base2[0].image = pos2[1];
                            }
                        }else if(hover(base2[1].pos,x,y)){
                            if(base2[1].direction == 1){
                                base2[1].direction = 0;
                                base2[1].image = pos2[0];
                            }else{
                                base2[1].direction = 1;
                                base2[1].image = pos2[1];
                            }
                        }
                    }else if(hover(locked->pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT) && locked->image == unlocked){
                        SDL_Delay(1000);
                        SDL_FreeSurface(screen.image);
                        SDL_FreeSurface(circuit.image);
                        SDL_FreeSurface(locked->image);
                }
                break;
            }
        }
        if(base3[0].direction == 1 && base3[1].direction == 0 && base3[2].direction == 1 && base2[0].direction == 0 && base2[1].direction == 0){
            locked->image = unlocked;
        }else locked->image = lockked;
        SDL_BlitSurface(image.image,NULL,screen.image,&image.pos);
        SDL_BlitSurface(circuit.image,NULL,screen.image,&circuit.pos);
        SDL_BlitSurface(locked->image,NULL,screen.image,&locked->pos);
        SDL_BlitSurface(base3[0].image,NULL,screen.image,&base3[0].pos);
        SDL_BlitSurface(base3[1].image,NULL,screen.image,&base3[1].pos);
        SDL_BlitSurface(base3[2].image,NULL,screen.image,&base3[2].pos);
        SDL_BlitSurface(base2[0].image,NULL,screen.image,&base2[0].pos);
        SDL_BlitSurface(base2[1].image,NULL,screen.image,&base2[1].pos);
        SDL_Flip(screen.image);
    }
    SDL_FreeSurface(screen.image);
}