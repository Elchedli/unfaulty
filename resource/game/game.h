#ifndef GAME_H_INCLUDE
#define GAME_H_INCLUDE

typedef struct{
 	  SDL_Surface* src;
	  SDL_Rect pos, posprite;
  	int vie, time, prs, isJumping, isFalling, jump, dirMouse, dp, action, oldAction, anim[8], hp, speed, direction, currlvl, inPresent;
} Personnage;

typedef struct{
  	SDL_Surface* present, * future, * collisionP, * collisionF, * resetP, * resetF;
  	SDL_Rect pos,zoompos;
} Map;

typedef struct{
  	SDL_Surface* src;
  	SDL_Rect pos, posprite;
  	int spawn, lvl, state, oldState;
} Object;

typedef struct{
  	SDL_Surface* src;
  	SDL_Rect pos, posprite;
} hudObject;

typedef struct{
  	Text vie, time, hp, hud;
  	hudObject HudObj[7];
} HUD;

typedef struct{
	SDL_Surface* src;
	SDL_Rect pos, posprite;
	int direction, dp, alive, etat, interval1, interval2, champsVue;
} NPC;

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
    int direction;
} protocol;

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
} simple;

void initBackground(Map *map);
void initText(Text* txt, char* content, TTF_Font* font, int x , int y);
void initHudObj(hudObject* HudObj, char* src, int x, int y);
void initHUD(HUD* hud);
void initPlayer(Personnage *player);
void initSinglePlayer(Personnage* player, Map* map, Object* entity, HUD *hud, NPC* npc);
void initObject(Object *entity,char* src, int x, int y, int xp, int yp, int lvl);
void moveGrabber(Object *entity, int *grabberState,int *move,Personnage *player,Map *map);
void afficherMap(SDL_Surface* *screen, Map map, Personnage player);
void afficherHUD(SDL_Surface* *screen, HUD *hud,Personnage player);
void afficherJoueur(Personnage player, Map map);
void deplacerJoueur(Personnage *player, Map *map, Object* entity, Uint8 *keys, keybinds kb, NPC* npc);
int AffichageJeuSingleplayer(SDL_Surface* screen, Personnage player, Map map, Object* entity, HUD hud, keybinds *kb, NPC* npc,Background pauseBackground,Background settingsBackground, Button *button,Mix_Chunk *SoundButtonHover, Mix_Chunk *SoundButtonClick, Text txt);
void scrolling(int pos, Map *map,Personnage player);
SDL_Color GetPixel(SDL_Surface* pSurface ,int x,int y);
int collision(Personnage player, int direction, Map map);
void gravity(Personnage *player, Map *map, NPC* npc,int move, Object* entity);
void resetScrolling(Personnage player, Map *map);
void jeuSingleplayer(SDL_Surface* screen, Button *button, keybinds *kb,Mix_Chunk *SoundButtonHover, Mix_Chunk *SoundButtonClick, Text txt, int newgame);
int collisionBoundingBox(NPC npc1, NPC npc2);
void afficherNPC(NPC* npc, Map *map);
void initNonPlayableCharacters(NPC* npc, Map *map);
void initNPC(NPC *npc, char* src, int x, int y, int xp, int yp, int direction, int interval1, int interval2, int champsVue);
void deplacerNPCs(NPC* npc, Map map, Personnage *player);
void deplacerAleatoire(NPC *npc);
void moveObjects(Object* entity, int* crushUp, int *grabberState,int *move,Personnage *player,Map *map);
void animateObjects(Object* entity);
#endif //GAME_H_INCLUDE
