/**
* @file quiz.c
* @brief il y a ici tous les fonctions de  l'enigme quiz.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_events.h"
#include "/usr/include/SDL/SDL_mouse.h"
#include "quiz.h"

int hover(SDL_Rect pos,int x,int y){
    Uint8 p;
    if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
    else return 0;
}

/**
* @brief initialiser les donnees de l'enigme.
* @param quiz e : obtenir les fichiers binaires contien les questions et reponse.
* @param rest r: obtenir les fichiers binaires contien l'interface et titre.
* @return Initialisation de l'enigme
*/

int initialiser(quiz *e,rest *r){
    int var;
    srand(time(0));
    var=(rand() % (3-1+1))+1;
    FILE* f=fopen("quiz.bin","rb");
    FILE* f1=fopen("rest.bin","rb");
    fread(&(*e),sizeof(quiz),var,f);
    fread(&(*r),sizeof(rest),1,f1);
    fclose(f);
    fclose(f1);
    if(var == 1){
        e->word.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme 1/word1.png");
        e->top.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme 1/e1i1.png");
        e->middle.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme 1/e1c2.png");
        e->bottom.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme 1/e1i3.png");
    }else if(var == 2){
        e->word.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/engime2/word2.png");
        e->top.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/engime2/e2i1.png");
        e->middle.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/engime2/e2i2.png");
        e->bottom.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/engime2/e2c3.png");
    }else if(var == 3){
        e->word.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme3/word3.png");
        e->top.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme3/e3i1.png");
        e->middle.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme3/e3i2.png");
        e->bottom.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/enigme3/e3c3.png");
    }
    r->locked.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/incorrect2.png");
    r->unlocked.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/correct1.png");
    r->interface.image = IMG_Load("/home/shidono/Desktop/enigmequestion/images/interface.png");
    return var;
}

/**
* @brief afficher et modifier les donnees de l'enigme.
* @param SDL_Surface *screen : affiche l'ecran.
* @param quiz e : utilise la structure obtenu di fichier binaire contien les questions et reponse.
* @param rest r: utilise la structure obtenu du fichier binaire contien interface et titre.
* @param SDL_Event event : fait les actions generer pas le hardware.
* @param int var,*vie,*access : var est l aleatoire des enigmes vie et access depond si l'enigme est fini ou echouée.
* @return affichage de l'enigme.
*/
void afficher(SDL_Surface *screen,quiz e,rest r,int var,int *vie,int *access){
    int done = 1,x,y;
    SDL_Event event;   
    while(done){
        SDL_BlitSurface(r.interface.image,NULL,screen,&r.interface.pos);
        SDL_BlitSurface(e.word.image,NULL,screen,&e.word.pos);
        SDL_BlitSurface(e.top.image,NULL,screen,&e.top.pos);
        SDL_BlitSurface(e.middle.image,NULL,screen,&e.middle.pos);
        SDL_BlitSurface(e.bottom.image,NULL,screen,&e.bottom.pos);
        SDL_Flip(screen);
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if(hover(e.top.pos,x,y) || hover(e.middle.pos,x,y) || hover(e.bottom.pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        if((var == 1 && hover(e.middle.pos,x,y)) || ((var == 2 || var == 3) && hover(e.bottom.pos,x,y))){
                            SDL_BlitSurface(r.unlocked.image,NULL,screen,&r.unlocked.pos);
                            (*access) = 1;
                        }else{
                           SDL_BlitSurface(r.locked.image,NULL,screen,&r.locked.pos);
                            (*vie)--; 
                        }
                        SDL_BlitSurface(r.interface.image,NULL,screen,&r.interface.pos);
                        SDL_BlitSurface(e.top.image,NULL,screen,&e.top.pos);
                        SDL_BlitSurface(e.middle.image,NULL,screen,&e.middle.pos);
                        SDL_BlitSurface(e.bottom.image,NULL,screen,&e.bottom.pos);
                        SDL_Flip(screen);
                        SDL_Delay(1000);
                        done = 0;
                    }
                break;
            }
        }
    }
    SDL_FreeSurface(screen);
}
