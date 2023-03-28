/**
* @file quiz.h
* @brief il y a ici les structures et la liaison des procedures de l'enigme.
*/
#ifndef QUIZ_H_INCLUDE
#define QUIZ_H_INCLUDE

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
}entity;

typedef struct{
	entity word;
	entity top,middle,bottom;
}quiz;

typedef struct{
	entity locked;
    entity unlocked;
    entity interface;
}rest;

int hover(SDL_Rect pos,int x,int y);

int initialiser(quiz *e,rest *r);

void afficher(SDL_Surface *screen,quiz e,rest r,int var,int *vie,int *access);

#endif //GAME_H_INCLUDE