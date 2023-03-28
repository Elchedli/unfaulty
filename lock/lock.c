/**
* @file lock.c
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
#include "/usr/include/SDL/SDL_rotozoom.h"
#include "lock.h"

int hover(SDL_Rect pos,int x,int y){
    Uint8 p;
    if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
    else return 0;
}
/**
* @brief initialiser les donnees de l'enigme.
* @param serrure *lock : adresse pour changer avec surface et position du serrure.
* @param serrure *lockprick : adresse pour changer avec surface et position du poignée.
* @param SDL_Rect *rec : adresse pour changer la position du rotozoom du serrure.
* @param SDL_Rect* *yaru : adresse pour changer la taille et l'angle du serrure.
* @return Initialisation de l'enigme
*/
void initialiser(serrure *lock,serrure *lockpick,SDL_Rect *rec,SDL_Surface* *yaru){
	
    lockpick->image = IMG_Load("/home/shidono/Desktop/godsake/pics/lock.png");
    lock->image = IMG_Load("/home/shidono/Desktop/godsake/pics/bigsi.png");
    (*yaru) = lock->image;

    lockpick->pos.x = 250;
    lockpick->pos.y = 50;

    lock->pos.x = 355;
    lock->pos.y = 160;

    (*rec) = lock->pos;

}
/**
* @brief afficher et modifier les donnees de l'enigme.
* @param int *vie : modifier vie si le personnage a cliquer dehors la serrure.
* @param int *access : modifie access si le personnage a completer l'enigme.
* @param SDL_Surface* screen: afficher l'ecran.
* @param SDL_Event event : fait les actions generer pas le hardware.
* @return affichage de l'enigme
*/
void afficher(int *vie,int *access,SDL_Surface* screen,SDL_Event event,serrure lock,serrure lockpick,SDL_Rect *rec,SDL_Surface* *yaru){
	SDL_Surface* rotateimage;
	int done=1,x=0,y=0,angle[3],var = 0,new=0,compteur = 0;
	angle[0] = 0;
    angle[1] = 20;
    angle[2] = -20;
    while(done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    if(hover((*rec),x,y) & SDL_BUTTON(SDL_BUTTON_LEFT)){
                        while(new == var){
                            srand(time(0));
                            var=(rand() % (2-0+1))+0;
                            printf("new : %d\n",new);
                            printf("var : %d\n",var);

                        }
                        new = var;
                        if(new != 0){
                            rec->x = 330;
                            rec->y = 140;
                        }else{
                            rec->x = 355;
                            rec->y = 160;
                        }
                        compteur++;
                        if(compteur == 5){
                            (*yaru) = rotozoomSurface(lock.image,0,1.1,1);
                            rotateimage=rotozoomSurface((*yaru),0,1.0,0);
                            SDL_FillRect(screen,NULL,0);
                            SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
                            SDL_BlitSurface(rotateimage,NULL,screen,&(*rec));
                            SDL_Flip(screen);
                            SDL_Delay(1000);
                            (*access) = 1;
                            done = 0;
                            printf("access = %d \n",*access);
                        }
                    }else if(hover(lockpick.pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                         SDL_FillRect(screen,NULL,0);
                         SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
                         SDL_Flip(screen);
                         SDL_Delay(2000);
                         (*vie)--;
                         SDL_FreeSurface(lockpick.image);
                          SDL_FreeSurface(screen);
                         done = 0;
                         printf("vie = %d \n",*vie);
                    }
                break;
            }
        }
        if(done){
            rotateimage=rotozoomSurface(lock.image,angle[new],1.0,0);
            SDL_FillRect(screen,NULL,0);
            SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
            SDL_BlitSurface(rotateimage,NULL,screen,&(*rec));
            SDL_Flip(screen);
        }
    }
    SDL_FreeSurface(lockpick.image);
}