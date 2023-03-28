prog:lock.o main.o
	gcc lock.o main.o -o prog -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx
lock.o:lock.c
	gcc -c lock.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx
main.o:main.c
	gcc -c main.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -lSDL_gfx