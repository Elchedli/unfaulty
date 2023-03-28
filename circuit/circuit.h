/**
* @file circuit.h
* @brief il y a ici les structures et la liaison des procedures de l'enigme.
*/
#ifndef CIRCUIT_H_INCLUDE
#define CIRCUIT_H_INCLUDE


typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
    int direction;
}protocol;

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
}simple;

int hover(SDL_Rect pos,int x,int y);
//
void initialiser(simple *screen,protocol base3[],protocol base2[],SDL_Surface* pos3[],SDL_Surface* pos2[],SDL_Surface* *unlocked,SDL_Surface* *lockked,simple *circuit,simple *locked,simple *image);

void afficher(simple screen, protocol base3[], protocol base2[], SDL_Surface* pos3[], SDL_Surface* pos2[], SDL_Surface* unlocked, SDL_Surface* lockked,simple circuit, simple *locked, SDL_Event event, simple image);
#endif //GAME_H_INCLUDE