#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_ttf.h"
#include "resource/menu/menu.h"
#include "resource/game/game.h"
#include "resource/settings/settings.h"


int main(){
	SDL_Surface *screen;
	Mix_Music *MenuMusic;
	Mix_Chunk *SoundButtonHover, *SoundButtonClick;
	Button button[31];
	Background menu, menutop, menuExit, menuSingleplayer, NULLL, settingsBackground, circle;
	Text title, txt;
	Sprite smoke,dust;
	keybinds kb;
	NULLL.src = NULL;
	int done = 0, choix, poskeys = -1;
	initGame(&screen, &title, &smoke, &dust, button, &menu, &menutop, &menuExit, &MenuMusic, &SoundButtonHover, &SoundButtonClick, &menuSingleplayer, &kb, &settingsBackground, &circle, &txt);
	cinematiqueLJ(screen);
	//Mix_PlayMusic(MenuMusic, -1);
	while(!done){
		choix = mainMenu(screen, title, smoke, dust, menu, menutop, button, SoundButtonHover, SoundButtonClick, &poskeys, MenuMusic);
		switch(choix){
			case 1:
				choix = subMenu(screen, menu, button, SoundButtonHover, SoundButtonClick, NULLL, menutop, 4, 7);
				switch(choix){
					case 5:
					Mix_HaltMusic();
						choix = subMenu(screen, menu, button, SoundButtonHover, SoundButtonClick, menuSingleplayer, menutop, 19, 21);
						switch(choix){
							case 20:
								jeuSingleplayer(screen, button, &kb, SoundButtonHover, SoundButtonClick, txt,	1);
								break;
							case 21:
								jeuSingleplayer(screen, button, &kb, SoundButtonHover, SoundButtonClick, txt, 0);
								break;
						}
						break;
					case 6:
						//jeuMultiplayer();
						break;
				}
				break;
			case 2:
				settingsMenu(screen, menutop, menu, button, SoundButtonHover, SoundButtonClick, settingsBackground, circle, 0, &kb, 10, 15, txt);
				break;
			case 3:
				creditsMenu();
				break;
			case 4:
				choix = subMenu(screen, menu, button, SoundButtonHover, SoundButtonClick, menuExit, menutop, 7, 9);
				if(choix == 8){
					done = 1;
				}
				break;
		}
	}
	SDL_FreeSurface(screen);
	SDL_FreeSurface(menu.src);
	SDL_FreeSurface(menutop.src);
	SDL_FreeSurface(menuExit.src);
	SDL_FreeSurface(title.message);
	TTF_CloseFont(title.font);
	Mix_FreeChunk(SoundButtonClick);
	Mix_FreeChunk(SoundButtonHover);
	Mix_FreeMusic(MenuMusic);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
