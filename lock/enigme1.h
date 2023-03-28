/**
* @brief il y a ici les structures et la liaison des procedures de l'enigme.
*/
typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
}serrure;

void enigme1(SDL_Surface *screen,SDL_Event event);
