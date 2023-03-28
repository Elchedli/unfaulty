/**
* @file main.c
* @brief circuit enigme quiz.
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
#include "quiz.h"
//
int main(){
	quiz e;
	rest r;
	SDL_Surface *screen;
	int var,access=0,vie = 3;
	screen = SDL_SetVideoMode(1000, 550, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	var = initialiser(&e,&r);
	afficher(screen,e,r,var,&vie,&access);
	return 0;
}