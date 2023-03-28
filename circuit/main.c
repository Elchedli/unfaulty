/**
* @file main.c
* @brief circuit enigme.
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
#include "circuit.h"
//
int main(){
	protocol base3[3],base2[2];
    SDL_Surface *pos3[4],*pos2[2],*unlocked,*lockked;
    simple screen,image,circuit,locked;
    SDL_Event event;
	initialiser(&screen,base3,base2,pos3,pos2,&unlocked,&lockked,&circuit,&locked,&image);
	afficher(screen,base3,base2,pos3,pos2,unlocked,lockked,circuit,&locked,event,image);
	return 0;
}//