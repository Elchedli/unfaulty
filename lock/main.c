/**
* @file main.c
* @brief lockpick enigme.
* @author Blindspot
* @version 0.1
* @date MAY 06, 2019
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


void main(){
	int vie = 3,access = 1;
	serrure lockpick,lock;
    SDL_Surface *screen,*yaru;
    SDL_Event event;
    SDL_Rect rec;
    screen = SDL_SetVideoMode(1000, 550, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    initialiser(&lock,&lockpick,&rec,&yaru);
    afficher(&vie,&access,screen,event,lock,lockpick,&rec,&yaru);
}