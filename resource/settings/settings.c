#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_ttf.h"
#include "../menu/menu.h"
#include "settings.h"

void settingsMenu(SDL_Surface* screen, Background menutop, Background menu, Button* button, Mix_Chunk* SoundButtonHover, Mix_Chunk* SoundButtonClick, Background settingsBackground, Background circle, int inGame, keybinds *kb, int j1, int j2, Text txt){
	int x, y, i, k, choix=-1, wait = 1;
	char ch[30];
	Uint8 keybindSelected;
	SDL_Event event;
	Background greySurface;
	greySurface.src = IMG_Load("materials/menu/greySurface.png");
	if(greySurface.src == NULL){
		printf("Unable to load greySurface File: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	greySurface.pos.x = 0;
	greySurface.pos.y = 0;
	Uint8 p;
	do{
		SDL_PumpEvents();
		SDL_PollEvent(&event);
		SDL_BlitSurface(menu.src, NULL, screen, &menu.pos);
		SDL_BlitSurface(greySurface.src, NULL, screen, &greySurface.pos);
		SDL_BlitSurface(menutop.src, NULL, screen, &menutop.pos);
		if(hover(button[30].pos, x, y)){
			button[30].current = button[30].hover;
		}else{
			button[30].current = button[30].regular;
		}
		SDL_BlitSurface(button[30].current, NULL, screen, &button[30].pos);
		for(k = 0; k < 4; k++){
			button[k].current = button[k].regular;
			SDL_BlitSurface(button[k].current, NULL, screen, &button[k].pos);
		}
		SDL_BlitSurface(settingsBackground.src, NULL, screen, &settingsBackground.pos);
		p = SDL_GetMouseState(&x, &y);
		i = 6;
		do{
			if(hover(button[i].pos, x, y)){
				button[i].current = button[i].hover;
				if(!button[i].soundPlayedHover){
					Mix_PlayChannel(-1, SoundButtonHover, 0);
					button[i].soundPlayedHover = 1;
				}
				if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
					if(!button[i].soundPlayedClick){
						Mix_PlayChannel(-1, SoundButtonClick, 0);
						button[i].soundPlayedClick = 1;
					}
					if(i == 6){
						choix = 0;
					}else{
						FILE* f = fopen("bin/keybinds.bin", "wb");
						if(f != NULL){
							fwrite(kb, sizeof(keybinds), 1, f);
							fclose(f);
						}
					}
				}else{
					button[i].soundPlayedClick = 0;
				}
			}else{
				button[i].current = button[i].regular;
				button[i].soundPlayedHover = 0;
			}
			SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
			i += 3;
		}while(i <= 9);
		for(i = j1; i < j2; i++){
			if(hover(button[i].pos, x, y)){
				if(!button[i].soundPlayedHover){
					Mix_PlayChannel(-1, SoundButtonHover, 0);
					button[i].soundPlayedHover = 1;
				}
				if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
					if(!button[i].soundPlayedClick){
						Mix_PlayChannel(-1, SoundButtonClick, 0);
						button[i].soundPlayedClick = 1;
					}
					button[i].current = button[i].hover;
					for(k = j1; k < j2; k++){
						if(k != i){
							button[k].current = button[k].regular;
						}
						SDL_BlitSurface(button[k].current, NULL, screen, &button[k].pos);
						switch(k){
							case 10:
								sprintf(ch, "%s", SDL_GetKeyName(kb->left));
								break;
							case 11:
								sprintf(ch, "%s", SDL_GetKeyName(kb->right));
								break;
							case 12:
								sprintf(ch, "%s", SDL_GetKeyName(kb->jump));
								break;
							case 13:
								sprintf(ch, "%s", SDL_GetKeyName(kb->interact));
								break;
							case 14:
								sprintf(ch, "%s", SDL_GetKeyName(kb->swaptime));
								break;
							}
							txt.message = TTF_RenderText_Solid(txt.font, ch, txt.textColor);
							txt.pos.x = button[k].pos.x + 10;
							txt.pos.y = button[k].pos.y + 3;
							SDL_BlitSurface(txt.message, NULL, screen, &txt.pos);
					}
					SDL_Event event;
					keybindSelected = 0;
					SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
					for(int j=i+1;j <j2;j++){
						SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
					}
					SDL_Flip(screen);
					wait = 1;
					while(wait){
						while( SDL_PollEvent( &event ) ){
		        	switch( event.type ){
								case SDL_KEYDOWN:
									keybindSelected = event.key.keysym.sym;
									break;
							}
					}
						if(keybindSelected > 0){
							wait = 0;
						}
					}
					switch(i){
						case 10:
							kb->left = keybindSelected;
							break;
						case 11:
						  kb->right = keybindSelected;
							break;
						case 12:
							kb->jump = keybindSelected;
							break;
						case 13:
							kb->interact = keybindSelected;
							break;
						case 14:
							kb->swaptime = keybindSelected;
							break;
				}
				}else{
					button[i].soundPlayedClick = 0;
				}
			}else{
				button[i].soundPlayedHover = 0;
			}
			SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
			switch(i){
				case 10:
					sprintf(ch, "%s", SDL_GetKeyName(kb->left));
					break;
				case 11:
					sprintf(ch, "%s", SDL_GetKeyName(kb->right));
					break;
				case 12:
					sprintf(ch, "%s", SDL_GetKeyName(kb->jump));
					break;
				case 13:
					sprintf(ch, "%s", SDL_GetKeyName(kb->interact));
					break;
				case 14:
					sprintf(ch, "%s", SDL_GetKeyName(kb->swaptime));
					break;
				}
				txt.message = TTF_RenderText_Solid(txt.font, ch, txt.textColor);
				txt.pos.x = button[i].pos.x + 10;
				txt.pos.y = button[i].pos.y + 3;
				SDL_BlitSurface(txt.message, NULL, screen, &txt.pos);
				button[i].current = button[i].regular;
		}
		SDL_Flip(screen);
	}while(choix == -1);
	SDL_FreeSurface(greySurface.src);
}
