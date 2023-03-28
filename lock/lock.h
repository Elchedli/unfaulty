/**
* @file lock.h
* @brief il y a ici les structures et la liaison des procedures de l'enigme.
*/
#ifndef LOCK_H_INCLUDE
#define LOCK_H_INCLUDE

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
}serrure;

void initialiser(serrure *lock,serrure *lockpick,SDL_Rect *rec,SDL_Surface* *yaru);

void afficher(int *vie,int *access,SDL_Surface* screen,SDL_Event event,serrure lock,serrure lockpick,SDL_Rect *rec,SDL_Surface* *yaru);

#endif //LOCK_H_INCLUDE