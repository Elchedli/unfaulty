game:game.o menu.o settings.o main.o
	gcc game.o settings.o menu.o main.o -o game -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx -lm
menu.o:resource/menu/menu.c
	gcc -c resource/menu/menu.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx
settings.o:resource/settings/settings.c
		gcc -c resource/settings/settings.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx
game.o:resource/game/game.c
	gcc -c resource/game/game.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx -lm
main.o:main.c
	gcc -c main.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx
