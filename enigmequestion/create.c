/**
* @file create.c
* @brief dans ce fichier deux fichiers binaires fait les appelles.
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

int main(){
	quiz e[3],h;
	rest r;
	SDL_Surface *screen;
	int var,access=0,vie = 3;

	e[0].word.pos.x = 129+270; e[0].word.pos.y = 32+117;
	e[0].top.pos.x = 167+267; e[0].top.pos.y = 95+117;
	e[0].middle.pos.x = 167+267; e[0].middle.pos.y = 142+117;
	e[0].bottom.pos.x = 167+267; e[0].bottom.pos.y = 188+117;
	e[1].word.pos = e[0].word.pos;e[1].top.pos = e[0].top.pos;e[1].top.pos = e[0].top.pos;e[1].middle.pos = e[0].middle.pos;e[1].bottom.pos = e[0].bottom.pos;
	e[2].word.pos = e[0].word.pos;e[2].top.pos = e[0].top.pos;e[2].middle.pos = e[0].middle.pos;e[2].bottom.pos = e[0].bottom.pos;

    r.interface.pos.x = 275; r.interface.pos.y = 125;
    r.locked.pos.x = 151+275; r.locked.pos.y = 262+117;
    r.unlocked.pos = r.locked.pos;
	FILE* f=fopen("quiz.bin","wb");
	FILE* f1=fopen("rest.bin","wb");
    fwrite(e,sizeof(quiz),3,f);
    fwrite(&r,sizeof(rest),1,f1);
    fclose(f);fclose(f1);


    printf("fait.\n"); 
	return 0;
}