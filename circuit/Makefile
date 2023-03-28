prog:circuit.o main.o
	gcc circuit.o main.o -o prog -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
circuit.o:circuit.c
	gcc -c circuit.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf 
main.o:main.c
	gcc -c main.c -g -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf	