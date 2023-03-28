#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_ttf.h"
#include "/usr/include/SDL/SDL_rotozoom.h"
#include "../menu/menu.h"
#include "game.h"

void initBackground(Map *map){
  map->present = IMG_Load("materials/maps/Level1.png");
  if(map->present == NULL){
    printf("Unable to load present map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->future = IMG_Load("materials/maps/Level3Future.png");
  if(map->future == NULL){
    printf("Unable to load future map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->resetP = IMG_Load("materials/maps/Level1.png");
  if(map->resetP == NULL){
    printf("Unable to load future map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->resetF = IMG_Load("materials/maps/Level3Future.png");
  if(map->resetF == NULL){
    printf("Unable to load future map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->collisionP = IMG_Load("materials/maps/Level1Collision.png");
  if(map->collisionP == NULL){
    printf("Unable to load collision for present map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->collisionF= IMG_Load("materials/maps/Level3Collision.png");
  if(map->future == NULL){
    printf("Unable to load collision for future map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->pos.x = 0;
  map->pos.y = 0;
  map->zoompos.x = 0;
  map->zoompos.y = 2250;
  map->zoompos.w = map->present->w;
  map->zoompos.h = map->present->h;
}

void initText(Text* txt, char* content, TTF_Font* font, int x , int y){
  txt->font = font;
  txt->textColor.r = 255;
  txt->textColor.g = 255;
  txt->textColor.b = 255;
  txt->message = TTF_RenderText_Solid(txt->font, content, txt->textColor);
  txt->pos.x = x;
  txt->pos.y = y;
}

void initHudObj(hudObject* HudObj, char* src, int x, int y){
  HudObj->src = IMG_Load(src);
  if(HudObj->src  == NULL){
    printf("Unable to load object : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  HudObj->pos.x = x;
  HudObj->pos.y = y;
  HudObj->posprite.x = 0;
  HudObj->posprite.y = 0;
  HudObj->posprite.w = HudObj->src->w;
  HudObj->posprite.h = HudObj->src->h;
}

void initHUD(HUD* hud){
  TTF_Font* font = TTF_OpenFont( "materials/fonts/CaviarDreams_Bold.ttf", 25);
  if(font == NULL){
    printf("Unable to load font : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  initText(&hud->vie, "x 3", font, 930, 30);
  initText(&hud->time, "00:00", font, 440, 500);
  initText(&hud->hp, "100", font, 35, 500);
  //initText(&hud->score, "0, font, 440, 500);
  //initHudObj(&hud->HudObj[0], "materials/HUD/heart.png", 35, 465);
  initHudObj(&hud->HudObj[0], "materials/HUD/heart.png", 870, 0);
  initHudObj(&hud->HudObj[1], "materials/HUD/Future.png", 790, 470);
  initHudObj(&hud->HudObj[2], "materials/HUD/Present.png", 790, 470);
  initHudObj(&hud->HudObj[3], "materials/HUD/NoWatch.png", 790, 470);
  initHudObj(&hud->HudObj[4], "materials/HUD/lifebarBg.png", 85, 500);
  initHudObj(&hud->HudObj[5], "materials/HUD/lifebar.png", 85, 500);
}

void initObject(Object *entity,char* src, int x, int y, int xp, int yp, int lvl){
	entity->src = IMG_Load(src);
  if(entity->src  == NULL){
    printf("Unable to load object : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
	entity->pos.x = x;
	entity->pos.y = y;
	entity->posprite.x = xp;
	entity->posprite.y = yp;
  entity->posprite.h = entity->src->h;
	entity->posprite.w = entity->src->w;
  entity->spawn = 1;
  entity->lvl = lvl;
  entity->state = 0;
  entity->oldState = 0;
}

void initPlayer(Personnage *player){
  player->src = IMG_Load("materials/sprites/game/ab-i5.png");
  if(player->src == NULL){
    printf("Unable to load character spritesheet: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  player->pos.x = 112;
  player->pos.y = 621;
  player->posprite.x = 1;
  player->posprite.y = 1;
  player->posprite.h = 82;
  player->posprite.w = 32;
  player->vie = 3;
  player->time = 0;
  player->prs = 1;
  player->isJumping = 0;
  player->isFalling = 0;
  player->jump = 0;
  player->dirMouse = 0;
  player->dp = 0;
  player->action = 4;
  player->oldAction = 4;
  player->anim[0] = 8; //WalkRight
  player->anim[1] = 8; //WalkLeft
  player->anim[2] = 8; //JumpRight
  player->anim[3] = 8; //jumpLeft
  player->anim[4] = 6; //IdleRight
  player->anim[5] = 6; //IdleLeft
  player->anim[6] = 1; //Slide
  player->anim[7] = 1; //PickUp
  player->hp = 100;
  player->speed = 5;
  player->direction = 1;
  player->currlvl = 1;
  player->inPresent = 1;
}

void initNPC(NPC *npc, char* src, int x, int y, int xp, int yp, int direction, int interval1, int interval2, int champsVue){
	npc->src = IMG_Load(src);
	if(npc->src == NULL){
    printf("Unable to load NPC spritesheet: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
	}
	npc->pos.x = x;
	npc->pos.y = y;
	npc->posprite.x = xp;
	npc->posprite.y = yp;
	npc->posprite.h = npc->src->h;
	npc->posprite.w = npc->src->w;
	npc->alive = 1;
	npc->direction = direction;
	npc->dp = 0;
  npc->interval1 = interval1;
  npc->interval2 = interval2;
  npc->champsVue = champsVue;
  npc->etat = 0;
}

void initNonPlayableCharacters(NPC* npc, Map *map){
  initNPC(&npc[0], "materials/sprites/game/NPCs/rat.png", 0, 0, 0, 0, 0, 0, 0, 0); //ho-c48
	initNPC(&npc[1], "materials/sprites/game/NPCs/rat.png", 4250, 837, 45, 0, 0, 4215, 4333, 481); //rat
	initNPC(&npc[2], "materials/sprites/game/NPCs/rat.png", 0, 0, 45, 0, 0, 0, 0, 0); //rat
	initNPC(&npc[3], "materials/sprites/game/NPCs/rat.png", 0, 0, 45, 0, 0, 0, 0, 0); //rat
	initNPC(&npc[4], "materials/sprites/game/NPCs/cockroach.png", 0, 0, 45, 0, 0, 0, 0, 0); //cockroach
	initNPC(&npc[5], "materials/sprites/game/NPCs/cockroach.png", 0, 0, 45, 0, 0, 0, 0, 0); //cockroach
	initNPC(&npc[6], "materials/sprites/game/NPCs/cockroach.png", 0, 0, 45, 0, 0, 0, 0, 0); //cockroach
}

void initImages(Personnage* player, Map *map, Object* entity, HUD *hud, NPC* npc){
  initObject(&entity[0], "materials/HUD/heart.png", entity[0].pos.x, entity[0].pos.y, entity[0].posprite.x, entity[0].posprite.y, entity[0].lvl);
  initObject(&entity[1], "materials/HUD/heart.png", entity[1].pos.x, entity[1].pos.y, entity[1].posprite.x, entity[1].posprite.y, entity[1].lvl);
  initObject(&entity[2], "materials/HUD/heart.png", entity[2].pos.x, entity[2].pos.y, entity[2].posprite.x, entity[2].posprite.y, entity[2].lvl);
  initObject(&entity[3], "materials/maps/grabber.png", entity[3].pos.x, entity[3].pos.y, entity[3].posprite.x, entity[3].posprite.y, entity[3].lvl);
  initObject(&entity[4], "materials/maps/topOf.png", entity[4].pos.x, entity[4].pos.y, entity[4].posprite.x, entity[4].posprite.y, entity[4].lvl);
  initObject(&entity[5], "materials/maps/crusher.png", entity[5].pos.x, entity[5].pos.y, entity[5].posprite.x, entity[5].posprite.y, entity[5].lvl);
  initObject(&entity[6], "materials/maps/crusher.png", entity[6].pos.x, entity[6].pos.y, entity[6].posprite.x, entity[6].posprite.y, entity[6].lvl);
  initObject(&entity[7], "materials/maps/crusher.png", entity[7].pos.x, entity[7].pos.y, entity[7].posprite.x, entity[7].posprite.y, entity[7].lvl);
  initObject(&entity[8], "materials/maps/elevatorDoor1.png", entity[8].pos.x, entity[8].pos.y, entity[8].posprite.x, entity[8].posprite.y, entity[8].lvl);
  map->present = IMG_Load("materials/maps/Level1.png");
  if(map->present == NULL){
    printf("Unable to load present map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->future = IMG_Load("materials/maps/Level1.png");
  if(map->future == NULL){
    printf("Unable to load future map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  map->collisionP = IMG_Load("materials/maps/Level1Collision.png");
  if(map->collisionP == NULL){
    printf("Unable to load collision for present map: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  TTF_Font* font = TTF_OpenFont( "materials/fonts/CaviarDreams_Bold.ttf", 25);
  if(font == NULL){
    printf("Unable to load font : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
  initText(&hud->vie, "x 3", font, 930, 30);
  initText(&hud->time, "00:00", font, 440, 500);
  initText(&hud->hp, "100", font, 35, 500);
  //initText(&hud->score, "0, font, 440, 500);
  //initHudObj(&hud->HudObj[0], "materials/HUD/heart.png", 35, 465);
  initHudObj(&hud->HudObj[0], "materials/HUD/heart.png", 870, 0);
  initHudObj(&hud->HudObj[1], "materials/HUD/Future.png", 790, 470);
  initHudObj(&hud->HudObj[2], "materials/HUD/Present.png", 790, 470);
  initHudObj(&hud->HudObj[3], "materials/HUD/NoWatch.png", 790, 470);
  initHudObj(&hud->HudObj[4], "materials/HUD/lifebarBg.png", 85, 500);
  initHudObj(&hud->HudObj[5], "materials/HUD/lifebar.png", 85, 500);

  player->src = IMG_Load("materials/sprites/game/ab-i5.png");
  if(player->src == NULL){
    printf("Unable to load character spritesheet: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  initNPC(&npc[0], "materials/sprites/game/NPCs/rat.png", npc[0].pos.x, npc[0].pos.y, npc[0].posprite.x, npc[0].posprite.y, npc[0].direction, npc[0].interval1, npc[0].interval2, npc[0].champsVue); //ho-c48
  initNPC(&npc[1], "materials/sprites/game/NPCs/rat.png", npc[1].pos.x, npc[1].pos.y, npc[1].posprite.x, npc[1].posprite.y, npc[1].direction, npc[1].interval1, npc[1].interval2, npc[1].champsVue); //rat
  initNPC(&npc[2], "materials/sprites/game/NPCs/rat.png", npc[2].pos.x, npc[2].pos.y, npc[2].posprite.x, npc[2].posprite.y, npc[2].direction, npc[2].interval1, npc[2].interval2, npc[2].champsVue); //rat
  initNPC(&npc[3], "materials/sprites/game/NPCs/rat.png", npc[3].pos.x, npc[3].pos.y, npc[3].posprite.x, npc[3].posprite.y, npc[3].direction, npc[3].interval1, npc[3].interval2, npc[3].champsVue); //rat
  initNPC(&npc[4], "materials/sprites/game/NPCs/cockroach.png", npc[4].pos.x, npc[4].pos.y, npc[4].posprite.x, npc[4].posprite.y, npc[4].direction, npc[4].interval1, npc[4].interval2, npc[4].champsVue); //cockroach
  initNPC(&npc[5], "materials/sprites/game/NPCs/cockroach.png", npc[5].pos.x, npc[5].pos.y, npc[5].posprite.x, npc[5].posprite.y, npc[5].direction, npc[5].interval1, npc[5].interval2, npc[5].champsVue); //cockroach
  initNPC(&npc[6], "materials/sprites/game/NPCs/cockroach.png", npc[6].pos.x, npc[6].pos.y, npc[6].posprite.x, npc[6].posprite.y, npc[6].direction, npc[6].interval1, npc[6].interval2, npc[6].champsVue); //cockroach
}

void initSinglePlayer(Personnage* player, Map *map, Object* entity, HUD *hud, NPC* npc){
  initObject(&entity[0], "materials/HUD/heart.png", 1976, 680, 0, 0, 1);
  initObject(&entity[1], "materials/HUD/heart.png", 1653, 218, 0, 0, 4);
  initObject(&entity[2], "materials/HUD/heart.png", 1508, 897, 0, 0, 5);
  initObject(&entity[3], "materials/maps/grabber.png", 814, 544, 0, 0, 1);
  initObject(&entity[4], "materials/maps/topOf.png", 798, 460, 0, 0, 1);
  initObject(&entity[5], "materials/maps/crusher.png", 1512, 511, 0, 0, 1);
  initObject(&entity[6], "materials/maps/crusher.png", 1622, 511, 0, 200, 1);
  initObject(&entity[7], "materials/maps/crusher.png", 1725, 511, 0, 100, 1);
  initObject(&entity[8], "materials/maps/elevatorDoor1.png", 3395, 954, 0, 0, 1);
  initObject(&entity[9], "materials/maps/elevatorDoor2.png", 1786, 925, 0, 0, 5);
  initObject(&entity[10], "materials/maps/elevator.png", 3415, 949, 0, 0, 1);
  initObject(&entity[11], "materials/maps/elevator.png", 27, 282, 0, 0, 2);
  entity[11].state = 0;
  initObject(&entity[12], "materials/maps/door.png", 2217, 282, 0, 0, 2);
  entity[12].state = 0;
  entity[12].oldState = 0;
  initObject(&entity[13], "materials/maps/door.png", 2525, 282, 0, 0, 2);
  entity[13].state = 0;
  entity[13].oldState = 0;
  initObject(&entity[14], "materials/maps/door.png", 42, 115, 0, 0, 3);
  entity[14].state = 0;
  initObject(&entity[15], "materials/maps/door.png", 353, 226, 0, 0, 3);
  entity[15].state = 0;
  initObject(&entity[16], "materials/maps/fireStarter.png", 1225, 533, 0, 0, 1);
  initObject(&entity[17], "materials/maps/shuriken.png", 2697, 1150, 0, 0, 1);
  initObject(&entity[18], "materials/maps/shuriken.png", 2869, 1151, 0, 0, 1);
  initObject(&entity[19], "materials/sprites/game/fire.png", 1227, 656, 0, 0, 1);
  entity[19].posprite.h = 140;
  entity[19].posprite.w = 140;
  initObject(&entity[20], "materials/sprites/game/smokeCleaner.png", 119, 245, 0, 0, 3);
  entity[20].state = 0;
  entity[20].posprite.h = entity[20].src->h;
  entity[20].posprite.w = 24;
  initObject(&entity[21], "materials/sprites/game/smokeCleaner.png", 196, 245, 0, 0, 3);
  entity[21].state = 0;
  entity[21].posprite.h = entity[21].src->h;
  entity[21].posprite.w = 24;
  initObject(&entity[22], "materials/sprites/game/smokeCleaner.png", 269, 245, 0, 0, 3);
  entity[22].state = 0;
  entity[22].posprite.h = entity[22].src->h;
  entity[22].posprite.w = 24;
  initObject(&entity[23], "materials/sprites/game/fire.png", 173, 625, 0, 0, 5);
  entity[23].posprite.h = 140;
  entity[23].posprite.w = 140;
  entity[23].state = 0;
  entity[23].spawn = 1;
  initObject(&entity[24], "materials/sprites/game/theEye.png", 1500, 70, 0, 0, 2);
  entity[24].posprite.w = entity[24].src->w / 2;
  initBackground(map);
  initHUD(hud);
  initPlayer(player);
  initNonPlayableCharacters(npc, map);
}

void afficherMap(SDL_Surface* *screen, Map map, Personnage player){
  if(player.inPresent){
    SDL_BlitSurface(map.present ,&map.zoompos,*screen, &map.pos);
  }else{
    SDL_BlitSurface(map.future ,&map.zoompos,*screen, &map.pos);
  }
}

void UpdateText(Text* txt, char content[]){
  txt->message = TTF_RenderText_Solid(txt->font, content, txt->textColor);
}

void afficherHUD(SDL_Surface* *screen, HUD *hud, Personnage player){
  SDL_BlitSurface(hud->HudObj[0].src ,NULL,*screen, &hud->HudObj[0].pos);
  SDL_BlitSurface(hud->HudObj[3].src ,NULL,*screen, &hud->HudObj[3].pos);
  SDL_BlitSurface(hud->HudObj[4].src ,NULL,*screen, &hud->HudObj[4].pos);
  SDL_BlitSurface(hud->HudObj[5].src ,&hud->HudObj[5].posprite,*screen, &hud->HudObj[5].pos);
  SDL_BlitSurface(hud->vie.message ,NULL,*screen, &hud->vie.pos);
  SDL_BlitSurface(hud->time.message ,NULL,*screen, &hud->time.pos);
  SDL_BlitSurface(hud->hp.message ,NULL,*screen, &hud->hp.pos);
}

void afficherObjects(Map *map,Object* entity,int x, int y, Personnage player, SDL_Surface* rotation1, SDL_Surface* rotation2){
  int i;
  if(entity[24].spawn && entity[24].lvl == player.currlvl){
      SDL_BlitSurface(entity[24].src, &entity[24].posprite, map->present, &entity[24].pos);
  }
  if(entity[23].spawn && entity[23].state == 1 && entity[23].lvl == player.currlvl){
      SDL_BlitSurface(entity[23].src, &entity[23].posprite, map->future, &entity[23].pos);
  }
  for(i = 19; i < 23; i++){
    if(entity[i].spawn && entity[i].state != 0 && entity[i].lvl == player.currlvl){
        SDL_BlitSurface(entity[i].src, &entity[i].posprite, map->present, &entity[i].pos);
    }
  }
  for(i = x; i < y; i++){
    if(entity[i].spawn && entity[i].lvl == player.currlvl && i != 16 && i != 17){
      SDL_BlitSurface(entity[i].src, &entity[i].posprite, map->present, &entity[i].pos);
    }
  }
  if(entity[17].lvl == player.currlvl){
    SDL_BlitSurface(rotation1, &entity[17].posprite, map->present, &entity[17].pos);
    SDL_BlitSurface(rotation2, &entity[18].posprite, map->present, &entity[18].pos);
  }
}

void moveCrusher(Object *entity, int *crushUp, Personnage *player){
  NPC playerNPC, CrusherNPC;
  if(*crushUp){
    if(entity->posprite.y <= 0){
      *crushUp = 0;
    }else{
      entity->posprite.y -= 4;
    }
    playerNPC.pos = player->pos;
    playerNPC.src = player->src;
    CrusherNPC.pos = entity->pos;
    CrusherNPC.pos.y = entity->pos.y - entity->posprite.y;
    CrusherNPC.src = entity->src;
    if(collisionBoundingBox(playerNPC, CrusherNPC)){
        player->hp -= 20;
        *crushUp = !*crushUp;
    }
  }else{
    if(entity->posprite.y >= 220){
      *crushUp = 1;
    }else{
      entity->posprite.y += 4;
    }
  }
}

void moveGrabber(Object *entity, int *grabberState,int *move,Personnage *player,Map *map){
  switch(*grabberState){
    case 0:
      if(entity->posprite.y <= 95){
        entity->posprite.y += 5;
      }else{
        if(entity->pos.x <= 1030){
          *grabberState = 2;
        }else{
          *grabberState = 3;
        }
      }
      break;
    case 1:
      if(entity->posprite.y > 0){
        entity->posprite.y -= 5;
      }else{
        *grabberState = 0;
      }
      if(move && entity->pos.x > 800 && entity->pos.x < 1030){
        NPC playerNPC, grabberNPC;
        playerNPC.pos = player->pos;
        playerNPC.src = player->src;
        grabberNPC.pos = entity->pos;
        grabberNPC.pos.y -= entity->posprite.y;
        grabberNPC.src = entity->src;
        if(collisionBoundingBox(playerNPC, grabberNPC)){
          *move = 0;
          *grabberState = 0;
          player->action = 7;
        }
      }
      if((*move) == 0 && entity->pos.x > 814 && player->pos.x < 1100 && entity->posprite.y >= 82){
          *move = 1;
          map->zoompos.x = 813;
      }
      break;
    case 2:
      if(entity->pos.x <= 1030){
        entity->pos.x+=5;
      }else{
        *grabberState = 1;
      }
      break;
    case 3:
      if(entity->pos.x >= 814){
        entity->pos.x-=5;
      }else{
        *grabberState = 1;
      }
      break;
  }
  if((*move) == 0 && player->pos.x > 800 && player->pos.x < 1100){
    player->action = 7;
    player->pos.x = entity->pos.x;
    if(*grabberState == 0){
      player->pos.y -= 5;
      scrolling(1, map,*player);
    }else{
      if(*grabberState == 1){
        player->pos.y += 5;
        scrolling(0, map,*player);
      }
    }
  }
}

void moveObjects(Object* entity, int* crushUp, int *grabberState,int *move,Personnage *player,Map *map){
  if(player->currlvl == 1){
    moveCrusher(&entity[5], &crushUp[0], player);
    moveCrusher(&entity[6], &crushUp[1], player);
    moveCrusher(&entity[7], &crushUp[2], player);
    moveGrabber(&entity[3], grabberState, move, player, map);
  }
}

void afficherJoueur(Personnage player, Map map){
    if(player.inPresent){
        SDL_BlitSurface(player.src, &player.posprite, map.present, &player.pos);
    }else{
        SDL_BlitSurface(player.src, &player.posprite, map.future, &player.pos);
    }
}

void scrolling(int pos, Map *map,Personnage player){
  switch(pos){
    case 0:
      map->zoompos.x -= player.speed;
      break;
    case 1:
      map->zoompos.x += player.speed;
      break;
    case 2:
      map->zoompos.y++;
      break;
    case 3:
      map->zoompos.y--;
      break;
  }
}

SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y){
  SDL_Color color;
  Uint32 col = 0;
  char* pPosition = (char*) pSurface->pixels;
  pPosition += (pSurface->pitch * y);
  pPosition += (pSurface->format->BytesPerPixel * x);
  memcpy(&col, pPosition, pSurface->format->BytesPerPixel);
  SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
  return color;
}

int collision(Personnage player, int direction, Map map){
  int collision = 0, i = 0;
  SDL_Color color[3];
  if(player.inPresent){
      switch(direction){
        case 0:
          color[0] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y);
          color[1] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y + player.posprite.h / 2);
          color[2] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y + player.posprite.h);
          break;
        case 1:
          color[0] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y);
          color[1] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h / 2);
          color[2] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h);
          break;
        case 2:
          color[0] = GetPixel(map.collisionP, player.pos.x, player.pos.y + player.posprite.h + 1);
          color[1] = GetPixel(map.collisionP, player.pos.x +player.posprite.w / 2, player.pos.y + player.posprite.h + 1);
          color[2] = GetPixel(map.collisionP, player.pos.x+ player.posprite.w, player.pos.y + player.posprite.h + 1);
          break;
        case 3:
          color[0] = GetPixel(map.collisionP, player.pos.x, player.pos.y - 1);
          color[1] = GetPixel(map.collisionP, player.pos.x + player.posprite.w/2, player.pos.y - 1);
          color[2] = GetPixel(map.collisionP, player.pos.x+ player.posprite.w, player.pos.y - 1);
          break;
      }
  }else{
      switch(direction){
        case 0:
          color[0] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y);
          color[1] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y + player.posprite.h / 2);
          color[2] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y + player.posprite.h);
          break;
        case 1:
          color[0] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y);
          color[1] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h / 2);
          color[2] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h);
          break;
        case 2:
          color[0] = GetPixel(map.collisionF, player.pos.x, player.pos.y + player.posprite.h + 1);
          color[1] = GetPixel(map.collisionF, player.pos.x +player.posprite.w / 2, player.pos.y + player.posprite.h + 1);
          color[2] = GetPixel(map.collisionF, player.pos.x+ player.posprite.w, player.pos.y + player.posprite.h + 1);
          break;
        case 3:
          color[0] = GetPixel(map.collisionF, player.pos.x, player.pos.y - 1);
          color[1] = GetPixel(map.collisionF, player.pos.x + player.posprite.w/2, player.pos.y - 1);
          color[2] = GetPixel(map.collisionF, player.pos.x+ player.posprite.w, player.pos.y - 1);
          break;
      }
  }
  while(i < 3 && !collision){
    if(color[i].r == 0 && color[i].g == 0 && color[i].b == 0){
      collision = 1;
    }
    i++;
  }
  return collision;
}

int collisionDeath(Personnage player, Map map){
  int collision = 0, i = 0;
  SDL_Color color[12];
  if(player.inPresent){
      color[0] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y);
      color[1] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y + player.posprite.h / 2);
      color[2] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y + player.posprite.h);
      color[3] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y);
      color[4] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h / 2);
      color[5] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h);
      color[6] = GetPixel(map.collisionP, player.pos.x, player.pos.y + player.posprite.h + 1);
      color[7] = GetPixel(map.collisionP, player.pos.x +player.posprite.w / 2, player.pos.y + player.posprite.h + 1);
      color[8] = GetPixel(map.collisionP, player.pos.x+ player.posprite.w, player.pos.y + player.posprite.h + 1);
      color[9] = GetPixel(map.collisionP, player.pos.x, player.pos.y - 1);
      color[10] = GetPixel(map.collisionP, player.pos.x + player.posprite.w/2, player.pos.y - 1);
      color[11] = GetPixel(map.collisionP, player.pos.x+ player.posprite.w, player.pos.y - 1);
  }else{
      color[0] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y);
      color[1] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y + player.posprite.h / 2);
      color[2] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y + player.posprite.h);
      color[3] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y);
      color[4] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h / 2);
      color[5] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h);
      color[6] = GetPixel(map.collisionF, player.pos.x, player.pos.y + player.posprite.h + 1);
      color[7] = GetPixel(map.collisionF, player.pos.x +player.posprite.w / 2, player.pos.y + player.posprite.h + 1);
      color[8] = GetPixel(map.collisionF, player.pos.x+ player.posprite.w, player.pos.y + player.posprite.h + 1);
      color[9] = GetPixel(map.collisionF, player.pos.x, player.pos.y - 1);
      color[10] = GetPixel(map.collisionF, player.pos.x + player.posprite.w/2, player.pos.y - 1);
      color[11] = GetPixel(map.collisionF, player.pos.x+ player.posprite.w, player.pos.y - 1);
  }
  while(i < 12 && !collision){
    if(color[i].r == 0 && color[i].g == 0 && color[i].b == 255){
      collision = 1;
    }
    i++;
  }
  return collision;
}

int collisionChangeMap(Personnage player, Map map){
  int collision = 0, i = 0;
  SDL_Color color[12];
  if(player.inPresent){
      color[0] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y);
      color[1] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y + player.posprite.h / 2);
      color[2] = GetPixel(map.collisionP, player.pos.x - 5, player.pos.y + player.posprite.h);
      color[3] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y);
      color[4] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h / 2);
      color[5] = GetPixel(map.collisionP, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h);
      color[6] = GetPixel(map.collisionP, player.pos.x, player.pos.y + player.posprite.h + 1);
      color[7] = GetPixel(map.collisionP, player.pos.x +player.posprite.w / 2, player.pos.y + player.posprite.h + 1);
      color[8] = GetPixel(map.collisionP, player.pos.x+ player.posprite.w, player.pos.y + player.posprite.h + 1);
      color[9] = GetPixel(map.collisionP, player.pos.x, player.pos.y - 1);
      color[10] = GetPixel(map.collisionP, player.pos.x + player.posprite.w/2, player.pos.y - 1);
      color[11] = GetPixel(map.collisionP, player.pos.x+ player.posprite.w, player.pos.y - 1);
  }else{
      color[0] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y);
      color[1] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y + player.posprite.h / 2);
      color[2] = GetPixel(map.collisionF, player.pos.x - 5, player.pos.y + player.posprite.h);
      color[3] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y);
      color[4] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h / 2);
      color[5] = GetPixel(map.collisionF, player.pos.x + player.posprite.w + 5, player.pos.y + player.posprite.h);
      color[6] = GetPixel(map.collisionF, player.pos.x, player.pos.y + player.posprite.h + 1);
      color[7] = GetPixel(map.collisionF, player.pos.x +player.posprite.w / 2, player.pos.y + player.posprite.h + 1);
      color[8] = GetPixel(map.collisionF, player.pos.x+ player.posprite.w, player.pos.y + player.posprite.h + 1);
      color[9] = GetPixel(map.collisionF, player.pos.x, player.pos.y - 1);
      color[10] = GetPixel(map.collisionF, player.pos.x + player.posprite.w/2, player.pos.y - 1);
      color[11] = GetPixel(map.collisionF, player.pos.x+ player.posprite.w, player.pos.y - 1);
  }
  while(i < 12 && !collision){
    if(color[i].r == 0 && color[i].g == 255 && color[i].b == 0){
      collision = 1;
    }
    i++;
  }
  return collision;
}

int collisionBoundingBox(NPC npc1, NPC npc2){
	return !(npc1.pos.x + npc1.posprite.w < npc2.pos.x || npc1.pos.x > npc2.pos.x + npc2.src->w || npc1.pos.y + npc1.posprite.h < npc2.pos.y || npc1.pos.y > npc2.pos.y + npc2.src->h);
}

void resetScrolling(Personnage player, Map *map){
  map->zoompos.y = player.pos.y - 340;
}

int arduinoReadData(int *x){
    char chemin[]="/dev/ttyACM0";
    FILE*f;
    char c;
    f=fopen(chemin,"r");
    if(f == NULL)
        return(-1);
    fscanf(f,"%d",x);
    fclose(f);
    return(0);
}

void deplacerJoueur(Personnage *player, Map *map, Object* entity, Uint8 *keys, keybinds kb, NPC* npc){
  NPC playerNPC;
  int x;
  int movement=0;
  if(arduinoReadData(&movement) == -1){
    printf("Can't ready from arduino\n" );
  }else{
    printf("%d aaa\n", movement);
  }
  switch(player->action){
    case 0: case 2: case 4: case 6: case 7:
      player->action = 4;
      break;
    case 1: case 3: case 5:
      player->action = 5;
      break;
  }
  if(!player->isFalling && !player->isJumping && (SDL_GetMouseState(&x, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))){
    x += map->zoompos.x;
    if(x >= player->pos.x){
      player->dirMouse = 1;
      player->dp = x - player->pos.x;
    }else{
      player->dirMouse = 0;
      player->dp = player->pos.x - x;
    }
  }
  if(player->dp > 0){
    if(player->dirMouse){
      player->action = 0;
      if(!collision(*player, 1, *map) && !player->isJumping){
        if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[12].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 2 && entity[14].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[14].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[14].pos.x + entity[14].src->w)){
            if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[15].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[15].pos.x + entity[15].src->w)){
              if(player->pos.x < (map->zoompos.x + 500)){
            		player->pos.x+=player->speed;
                player->dp -= 5;
            	}else{
            		if(map->zoompos.x <= map->present->w){
                  scrolling(1,map,*player);
                  player->pos.x+=player->speed;
                  player->dp -= 5;
            		}else{
            			if(player->pos.x < map->present->w-75){
            				player->pos.x+=player->speed;
                    player->dp -= 5;
            			}
            		}
            	}
            }else{
                player->dp = 0;
            }
        }else{
          player->dp = 0;
        }
      }else{
        player->dp = 0;
      }
    }else{
      player->action = 1;
      if(!collision(*player, 0, *map) && !player->isJumping && !player->isFalling){
        if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x - 1 >= entity[12].pos.x && player->pos.x - 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 3 && entity[14].state != 2 && player->pos.x - 1 >= entity[14].pos.x && player->pos.x - 1 <= entity[14].pos.x + entity[14].src->w)){
            if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x - 1 >= entity[15].pos.x && player->pos.x - 1 <= entity[15].pos.x + entity[15].src->w) && !(player->currlvl == 3 && entity[13].state != 2 && player->pos.x - 1 >= entity[13].pos.x && player->pos.x - 1 <= entity[13].pos.x + entity[13].src->w)){
              if(player->pos.x > (map->zoompos.x + 100)){
                player->pos.x-=player->speed;
                player->dp -= 5;
            	}else{
            		if(map->zoompos.x > 0){
                    scrolling(0,map,*player);
                    player->pos.x-=player->speed;
                    player->dp -= 5;
                }else{
            			if(player->pos.x > 3){
            				player->pos.x-=player->speed;
                          player->dp -= 5;
            			}
            		}
            	}
            }else{
                player->dp = 0;
            }
        }else{
          player->dp = 0;
        }
      }else{
        player->dp = 0;
      }
    }
  }
  playerNPC.pos = player->pos;
  playerNPC.src = player->src;
  if((keys[kb.right] || movement == 4) && !collision(*player, 1, *map) && !player->isJumping && !player->isFalling){
      if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[12].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 3 && entity[14].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[14].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[14].pos.x + entity[14].src->w)){
          if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[15].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[15].pos.x + entity[15].src->w)){
              player->action = 0;
              player->direction = 1;
              player->dp = 0;
              if(player->pos.x < (map->zoompos.x + 500)) {
            		player->pos.x+=player->speed;
            	}else{
            		if(map->zoompos.x <= map->present->w){
                  scrolling(1,map,*player);
                  player->pos.x+=player->speed;
            		}else{
            			if(player->pos.x < map->present->w-75){
            				player->pos.x+=player->speed;
            			}
            		}
            	}
            }
    }
  }
  if((keys[kb.left] || movement == 3) && !collision(*player, 0, *map) && !player->isJumping && !player->isFalling){
    if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x - 1 >= entity[12].pos.x && player->pos.x - 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 3 && entity[14].state != 2 && player->pos.x - 1 >= entity[14].pos.x && player->pos.x - 1 <= entity[14].pos.x + entity[14].src->w)){
        if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x - 1 >= entity[15].pos.x && player->pos.x - 1 <= entity[15].pos.x + entity[15].src->w) && !(player->currlvl == 3 && entity[13].state != 2 && player->pos.x - 1 >= entity[13].pos.x && player->pos.x - 1 <= entity[13].pos.x + entity[13].src->w)){
          player->direction = 0;
          player->action = 1;
          player->dp = 0;
        	if(player->pos.x > (map->zoompos.x + 100)){
            player->pos.x-=player->speed;
        	}else{
        		if(map->zoompos.x > 0){
                scrolling(0,map,*player);
                player->pos.x-=player->speed;
            }else{
        			if(player->pos.x > 20){
        				player->pos.x-=player->speed;
        			}
        		}
        	}
        }
    }
  }
  if((keys[kb.jump] || movement == 1 ) && !collision(*player, 3, *map) && collision(*player, 2, *map)){
    switch(player->action){
      case 0: case 2: case 4: case 6: case 7:
        player->action = 2;
        break;
      case 1: case 3: case 5:
        player->action = 3;
        break;
    }
    if(!player->isJumping){
  		player->isJumping = 1;
  	}
  }
  if(player->isJumping){
    switch(player->action){
      case 0: case 2: case 4: case 6: case 7:
        player->action = 2;
        break;
      case 1: case 3: case 5:
        player->action = 3;
        break;
    }
  	if(player->jump <= 30 && !collision(*player, 3, *map)){
    	player->jump+=4;
    	player->pos.y -= 10;
      if(player->jump >= 30){
        player->isJumping = 0;
        player->jump = 0;
        player->isFalling = 1;
      }
      switch(player->action){
        case 0: case 2: case 4: case 6: case 7:
          if(!collision(*player, 1, *map)){
              if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[12].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 3 && entity[14].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[14].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[14].pos.x + entity[14].src->w)){
                  if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[15].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[15].pos.x + entity[15].src->w)){
                      if(player->pos.x < (map->zoompos.x + 500)){
                    	player->pos.x+=5;
                        player->pos.x+=5;
                        }else{
                            if(player->pos.x < map->present->w-75){
                        	       player->pos.x+=5;
                            }
                        }
                }else{
                    if(player->pos.x < map->present->w-75){
                	       player->pos.x+=5;
                    }
                }
            }else{
              player->isFalling = 1;
            }
          }else{
            player->isFalling = 1;
          }
          break;
        case 1: case 3: case 5:
          if(!collision(*player, 0, *map)){
              if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x - 1 >= entity[12].pos.x && player->pos.x - 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 3 && entity[14].state != 2 && player->pos.x - 1 >= entity[14].pos.x && player->pos.x - 1 <= entity[14].pos.x + entity[14].src->w)){
                  if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x - 1 >= entity[15].pos.x && player->pos.x - 1 <= entity[15].pos.x + entity[15].src->w)  && !(player->currlvl == 3 && entity[13].state != 2 && player->pos.x - 1 >= entity[13].pos.x && player->pos.x - 1 <= entity[13].pos.x + entity[13].src->w)){
                      if(player->pos.x > (map->zoompos.x + 100)){
                        player->pos.x-=5;
                    	}else{
                    		if(map->zoompos.x > 0){
                            scrolling(0,map,*player);
                            player->pos.x-=5;
                        }else{
                    			if(player->pos.x > 20){
                    				player->pos.x-=5;
                    			}
                    		}
                    	}
                }else{
                    player->isFalling = 1;
                }
            }else{
              player->isFalling = 1;
            }
          }else{
            player->isFalling = 1;
          }
          break;
      }
  	}else{
      player->isJumping = 0;
      player->jump = 0;
    }
  }
  if(collision(*player, 3, *map)){
    player->isJumping = 0;
    player->jump = 0;
  }
  for(int i = 4; i < 7; i++){
    if(collisionBoundingBox(playerNPC, npc[i])){
      npc[i].alive = 0;
    }
  }
  for(int i = 0; i < 3; i++){
    if(entity[i].lvl == player->currlvl){
      NPC heartNPC;
      heartNPC.pos = entity[i].pos;
      heartNPC.pos.y -= entity[i].posprite.y;
      heartNPC.src = entity[i].src;
      if(collisionBoundingBox(playerNPC, heartNPC) && entity[i].spawn){
        player->vie++;
        entity[i].spawn = 0;
      }
    }
  }
  resetScrolling(*player, map);
}

void gravity(Personnage *player, Map *map, NPC* npc,int move, Object* entity){
  NPC playerNPC;
  Personnage check = *player;
  int i;
  playerNPC.pos = player->pos;
  playerNPC.src = player->src;
  if(move){
    if(!collision(*player, 2, *map) && !player->isJumping){
        switch(player->action){
          case 0: case 2: case 4: case 6: case 7:
            if(!collision(*player, 1, *map) && player->isFalling){
                if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[12].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 3 && entity[14].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[14].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[14].pos.x + entity[14].src->w)){
                    if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x + player->posprite.w  + 1 >= entity[15].pos.x && player->pos.x + player->posprite.w  + 1 <= entity[15].pos.x + entity[15].src->w)){
                        if(player->pos.x < (map->zoompos.x + 500)){
                      		player->pos.x+=5;
                      	}else{
                      		if(map->zoompos.x <= map->present->w){
                                scrolling(1,map,*player);
                                player->pos.x+=5;
                      		}else{
                      			if(player->pos.x < map->present->w-75){
                      				player->pos.x+=5;
                      			}
                      		}
                      	}
                }else{
                    player->isFalling = 0;
                }
              }else{
                player->isFalling = 0;
              }
            }else{
              player->isFalling = 0;
            }
            break;
          case 1: case 3: case 5:
            if(!collision(*player, 0, *map) && player->isFalling){
                if(!(player->currlvl == 2 && entity[12].state != 2 && player->pos.x - 1 >= entity[12].pos.x && player->pos.x - 1 <= entity[12].pos.x + entity[12].src->w) && !(player->currlvl == 3 && entity[14].state != 2 && player->pos.x - 1 >= entity[14].pos.x && player->pos.x - 1 <= entity[14].pos.x + entity[14].src->w)){
                    if(!(player->currlvl == 3 && entity[15].state != 2 && player->pos.x - 1 >= entity[15].pos.x && player->pos.x - 1 <= entity[15].pos.x + entity[15].src->w) && !(player->currlvl == 2 && entity[13].state != 2 && player->pos.x - 1 >= entity[13].pos.x && player->pos.x - 1 <= entity[13].pos.x + entity[13].src->w)){
                        if(player->pos.x > (map->zoompos.x + 100)){
                          player->pos.x-=5;
                      	}else{
                      		if(map->zoompos.x > 0){
                              scrolling(0,map,*player);
                              player->pos.x-=5;
                          }else{
                      			if(player->pos.x > 20){
                      				player->pos.x-=5;
                      			}
                      		}
                      	}
                    }else{
                        player->isFalling = 0;
                    }
              }else{
                player->isFalling = 0;
              }
            }else{
              player->isFalling = 0;
            }
            break;
        }
        check.pos.y += 10;
        while(collision(check, 2, *map)){
          check.pos.y--;
        }
        player->pos.y = check.pos.y+1;
        for(i = 1; i < 7; i++){
          if(collisionBoundingBox(playerNPC, npc[i])){
            npc[i].alive = 0;
          }
        }
    }else{
      player->isFalling = 0;
    }
  }
}

void afficherNPC(NPC* npc, Map *map){
	int i;
	for(i = 0; i < 7; i++){
		SDL_BlitSurface(npc[i].src, &npc[i].posprite, map->present, &npc[i].pos);
	}
}

void deplacerAleatoire(NPC *npc){
  srand(time(NULL));
  if(npc->dp == 0){
  	npc->direction = rand() % 2;
  	npc->dp = (rand() % 100) + 10;
	}
	if(npc->direction){
		if(npc->pos.x < npc->interval2 && npc->dp > 0){
			npc->pos.x++;
			npc->dp--;
		}else{
			npc->dp = 0;
		}
	}else{
		if(npc->pos.x > npc->interval1 && npc->dp > 0){
			npc->pos.x--;
			npc->dp--;
		}else{
			npc->dp = 0;
		}
	}
}

void deplacerNPCs(NPC* npc, Map map, Personnage *player){
	int i, distPersoEnnemi;
	for(i = 1; i < 4; i++){
		if(npc[i].alive){
      distPersoEnnemi = abs(npc[i].pos.x - player->pos.x);
	  	if(distPersoEnnemi > npc[i].champsVue){
	  		if(npc[i].pos.x < 880 || npc[i].pos.x > 100){
	  			npc[i].etat = 0;
	    	}else{
	    		npc[i].etat = 3;
	    	}
	    }else{
	    	if(distPersoEnnemi <= 5){
	    		npc[i].etat = 1;
	    	}else{
	    		npc[i].etat = 2;
	    	}
	    }
	    switch(npc[i].etat){
	    	case 0:
	    		deplacerAleatoire(&npc[i]);
	    		break;
	    	case 1:
	    		player->hp -= 2;
	    		break;
	    	case 2:
	    		if(npc[i].pos.x -player->pos.x > 0){
	    			npc[i].pos.x--;
	    		}else{
	    			npc[i].pos.x++;
	    		}
	    		break;
	    	case 3:
	    		if(npc[i].pos.x < 900){
	    			npc[i].pos.x++;
	    		}else{
	    			npc[i].pos.x--;
	    		}
	    		break;
	    }
		}
	}
  for(i = 4; i < 7; i++){
		if(npc[i].alive){
			deplacerAleatoire(&npc[i]);
		}
	}
}

void timer(Personnage *player,int *tempsAct,int *tempsPrec){
  *tempsAct = SDL_GetTicks();
  if (*tempsAct - *tempsPrec > 1000){
      player->time++;
      *tempsPrec = *tempsAct;
  }
}

void updateHUD(Personnage *player,int *tempsAct,int *tempsPrec,HUD *hud){
  char ch1[10];
  char hpc[3];
  char snum[20];
  timer(player,tempsPrec,tempsAct);
  sprintf(ch1, "x %d", player->vie);
  UpdateText(&hud->vie, ch1);
  int min = player->time /60;
  int sec = player->time - min * 60;
  if(min < 10){
    if(sec < 10){
      sprintf(snum, "0%d : 0%d", min, sec);
    }else{
      sprintf(snum, "0%d : %d", min, sec);
    }
  }else{
    if(sec < 10){
      sprintf(snum, "%d : 0%d", min, sec);
    }else{
      sprintf(snum, "%d : %d", min, sec);
    }
  }
  sprintf(hpc, "%d", player->hp);
  UpdateText(&hud->time, snum);
  UpdateText(&hud->hp, hpc);
  hud->HudObj[5].posprite.w = hud->HudObj[5].src->w;
  hud->HudObj[5].posprite.w -= (((100 - player->hp) * hud->HudObj[5].src->w) / 100);
}
void restartCheckpoint(Personnage *player, Map *map){
    if(player->currlvl == 1){
        if(player->pos.x <= map->present->w / 2){
            player->pos.x = 984;
            player->pos.y = 724;
            map->zoompos.x = 813;
            resetScrolling(*player, map);
        }else{
            player->pos.x = 2391;
            player->pos.y = 942;
            map->zoompos.x = 2241;
            resetScrolling(*player, map);
        }
    }else{
        if(player->currlvl == 2){
            player->pos.x = 208;
            player->pos.y = 298;
            map->zoompos.x = 0;
            resetScrolling(*player, map);
        }else{
            if(player->currlvl == 3){
                player->pos.x = 1718;
                player->pos.y = 255;
                map->zoompos.x = 1535;
                resetScrolling(*player, map);
            }else{
                if(player->currlvl == 4){
                    player->pos.x = 528;
                    player->pos.y = 334;
                    map->zoompos.x = 362;
                    resetScrolling(*player, map);
                }else{
                    if(player->currlvl == 5){
                        if(player->pos.x <= map->present->w / 3){
                            player->pos.x = 85;
                            player->pos.y = 62;
                            map->zoompos.x = 0;
                            resetScrolling(*player, map);
                        }else{
                            player->pos.x = 685;
                            player->pos.y = 604;
                            map->zoompos.x = 429;
                            resetScrolling(*player, map);
                        }
                    }
                }
            }
        }
    }
}

void animerPersonnage(Personnage *player){
	player->posprite.y = player->action * 158;
	if(player->oldAction != player->action || player->posprite.x + 123 >= 123 * player->anim[player->action]){
			player->posprite.x = 0;
		}else{
			player->posprite.x += 123;
	}
	player->oldAction = player->action;
}
void savegame(Map map,Personnage player,Object *entity, NPC *npc)
{
  FILE *f = fopen("saves/continue.save", "wb");
  if(f != NULL){
    fwrite(&map, sizeof(Map), 1, f);
    fwrite(&player, sizeof(Personnage), 1, f);
    fwrite(entity, sizeof(Object), 24, f);
    fwrite(npc, sizeof(NPC), 10, f);
    fclose(f);
  }

}

void settings(Map map, HUD hud, Personnage player, SDL_Surface* screen, keybinds *kb, Background settingsBackground, Button *button,Mix_Chunk *SoundButtonHover, Mix_Chunk *SoundButtonClick, int j1, int j2, Text txt){
  int x, y, i, k, choix=-1, wait = 1;
  char ch[20];
  Uint8 keybindSelected;
  SDL_Event event;
  Uint8 p;
  do{
    SDL_PumpEvents();
    SDL_PollEvent(&event);
    afficherMap(&screen, map, player);
    afficherHUD(&screen,&hud,player);
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
}

void gamePause(int *done,Map map, HUD hud,Personnage player,SDL_Surface* screen,Object *entity, NPC *npc, keybinds *kb,Background pauseBackground,Background settingsBackground, Button *button,Mix_Chunk *SoundButtonHover, Mix_Chunk *SoundButtonClick, Text txt)
{
  int x, y, choix = 0;
  SDL_Event event;
  int exit = 0;
  SDL_Surface* locked = IMG_Load("materials/HUD/GamePause/savegameLocked.png");
  Uint8 p;
  do{
    choix = 0;
    afficherMap(&screen, map, player);
    afficherHUD(&screen,&hud,player);
    SDL_BlitSurface(pauseBackground.src, NULL, screen, &pauseBackground.pos);
    p = SDL_GetMouseState(&x, &y);
    for(int i = 15; i < 19; i++){
      if(i != 16 || button[16].current != locked){
  			if(hover(button[i].pos, x, y)){
  				button[i].current = button[i].hover;
  				if(!button[i].soundPlayedHover){
  					button[i].soundPlayedHover = 1;
            Mix_PlayChannel(-1, SoundButtonHover, 0);
  				}
  				if(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
  					if(!button[i].soundPlayedClick){
  						button[i].soundPlayedClick = 1;
              Mix_PlayChannel(-1, SoundButtonClick, 0);
  					}
  					choix = (i - 15) + 1;
  				}else{
  					button[i].soundPlayedClick = 0;
  				}
  			}else{
  				button[i].current = button[i].regular;
  				button[i].soundPlayedHover = 0;
  			}
      }
			SDL_BlitSurface(button[i].current, NULL, screen, &button[i].pos);
		}
    SDL_Flip(screen);
    while( SDL_PollEvent( &event ) ){
      switch( event.type ){
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_ESCAPE)
            exit = 1;
          break;
      }
    }
    switch(choix){
      case 2:
        savegame(map, player, entity, npc);
        button[16].current = locked;
        break;
      case 3:
        settings(map, hud, player, screen, kb, settingsBackground, button, SoundButtonHover, SoundButtonClick, 10, 15, txt);
        break;
      case 4:
          *done = 1;
          break;
    }
  }while(!exit && choix != 1 && *done != 1);
  button[16].current = button[16].regular;
}

void animateObjects(Object* entity){
    int i = 19;
        if(entity[i].state != 0){
            entity[i].posprite.y = (entity[i].state - 1) * 184;
            if(entity[i].state == 1 || entity[i].state == 3){
            	if(entity[i].oldState != entity[i].state || entity[i].posprite.x + 139 >= 139 * 3){
            			entity[i].posprite.x = 0;
            		}else{
            			entity[i].posprite.x += 139;
            	}
            }else{
                if(entity[i].state == 2){
                    if(entity[i].oldState != entity[i].state || entity[i].posprite.x + 139 >= 139 * 4){
                			entity[i].posprite.x = 0;
                		}else{
                			entity[i].posprite.x += 139;
                	}
                }
            }
        }else{
            entity[i].posprite.x = 0;
            entity[i].posprite.y = 0;
        }
    	entity[i].oldState = entity[i].state;
    for(i = 20; i < 23; i++){
    	if(entity[i].posprite.x + 21 >= 21 * 6){
    	    entity[i].posprite.x = 0;
    	}else{
    		entity[i].posprite.x += 21;
        }
    }
    entity[23].posprite.y = 184;
    if(entity[23].posprite.x + 139 >= 139 * 4){
        entity[23].posprite.x = 0;
    }else{
        entity[23].posprite.x += 139;
    }
}

void initialiser(protocol base3[],protocol base2[],SDL_Surface* pos3[],SDL_Surface* pos2[],SDL_Surface* *unlocked,SDL_Surface* *lockked,simple *circuit,simple *locked,simple *image){
	image->image = IMG_Load("/home/shidono/Desktop/circuit/background.png");
    circuit->image = IMG_Load("/home/shidono/Desktop/circuit/plan.png");
    (*unlocked) = IMG_Load("/home/shidono/Desktop/circuit/unlocked.png");
    (*lockked) = IMG_Load("/home/shidono/Desktop/circuit/locked.png");
    pos3[0] = IMG_Load("/home/shidono/Desktop/circuit/3pos1.png");
    pos3[1] = IMG_Load("/home/shidono/Desktop/circuit/3pos2.png");
    pos3[2] = IMG_Load("/home/shidono/Desktop/circuit/3pos3.png");
    pos3[3] = IMG_Load("/home/shidono/Desktop/circuit/3pos4.png");
    pos2[0] = IMG_Load("/home/shidono/Desktop/circuit/2pos1.png");
    pos2[1] = IMG_Load("/home/shidono/Desktop/circuit/2pos2.png");
    locked->image = (*lockked);

    base3[0].image = pos3[0];
    base3[1].image = pos3[2];
    base3[2].image = pos3[0];
    base2[0].image = pos2[1];
    base2[1].image = pos2[1];


	base3[0].direction = 3;
    base3[1].direction = 2;
    base3[2].direction = 1;
    base2[0].direction = 0;
    base2[1].direction = 1;

    image->pos.x = 0;
    image->pos.y = 0;

    circuit->pos.x = 0;
    circuit->pos.y = 0;

    base3[0].pos.x = 58;
    base3[0].pos.y = 181;

    base3[1].pos.x = 290;
    base3[1].pos.y = 180;

    base3[2].pos.x = 495;
    base3[2].pos.y = 247;

    base2[0].pos.x = 241;
    base2[0].pos.y = 322;

    base2[1].pos.x = 670;
    base2[1].pos.y = 256;

    locked->pos.x = 863;
    locked->pos.y = 282;
}

int afficher(SDL_Surface* screen, protocol base3[], protocol base2[], SDL_Surface* pos3[], SDL_Surface* pos2[], SDL_Surface* unlocked, SDL_Surface* lockked,simple circuit, simple *locked, SDL_Event event, simple image){
	int done = 1,x = 0,y = 0,a = 0,b = 0,c = 0;
	SDL_BlitSurface(image.image,NULL,screen,&image.pos);
    SDL_BlitSurface(circuit.image,NULL,screen,&circuit.pos);
    SDL_BlitSurface(locked->image,NULL,screen,&locked->pos);
    SDL_BlitSurface(base3[0].image,NULL,screen,&base3[0].pos);
    SDL_BlitSurface(base3[1].image,NULL,screen,&base3[1].pos);
    SDL_BlitSurface(base3[2].image,NULL,screen,&base3[2].pos);
    SDL_BlitSurface(base2[0].image,NULL,screen,&base3[0].pos);
    SDL_BlitSurface(base2[1].image,NULL,screen,&base2[1].pos);
    SDL_Flip(screen);
    while(done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&x,&y);
                    a = hover(base3[0].pos,x,y);
                    b = hover(base3[1].pos,x,y);
                    c = hover(base3[2].pos,x,y);
                    if(( a || b || c) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        if(a){
                            if(base3[0].direction == 3){
                                base3[0].direction = 0;
                                base3[0].image = pos3[0];
                            }else{
                                base3[0].direction++;
                                base3[0].image = pos3[base3[0].direction];
                            }
                        }else if(b){
                            if(base3[1].direction == 3){
                                base3[1].direction = 0;
                                base3[1].image = pos3[0];
                            }else{
                                base3[1].direction++;
                                base3[1].image = pos3[base3[1].direction];
                            }
                        }else if(c){
                            if(base3[2].direction == 3){
                                base3[2].direction = 0;
                                base3[2].image = pos3[0];
                            }else{
                                base3[2].direction++;
                                base3[2].image = pos3[base3[2].direction];
                            }
                        }
                    }else if((hover(base2[0].pos,x,y) || hover(base2[1].pos,x,y)) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        if(hover(base2[0].pos,x,y)){
                            if(base2[0].direction == 1){
                                base2[0].direction = 0;
                                base2[0].image = pos2[0];
                            }else{
                                base2[0].direction = 1;
                                base2[0].image = pos2[1];
                            }
                        }else if(hover(base2[1].pos,x,y)){
                            if(base2[1].direction == 1){
                                base2[1].direction = 0;
                                base2[1].image = pos2[0];
                            }else{
                                base2[1].direction = 1;
                                base2[1].image = pos2[1];
                            }
                        }
                    }else if(hover(locked->pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT) && locked->image == unlocked){
                        SDL_Delay(1000);
                        SDL_FreeSurface(screen);
                        SDL_FreeSurface(circuit.image);
                        SDL_FreeSurface(locked->image);
                        return 1;
                }
                break;
            }
        }
        if(base3[0].direction == 1 && base3[1].direction == 0 && base3[2].direction == 1 && base2[0].direction == 0 && base2[1].direction == 0){
            locked->image = unlocked;
        }else locked->image = lockked;
        SDL_BlitSurface(image.image,NULL,screen,&image.pos);
        SDL_BlitSurface(circuit.image,NULL,screen,&circuit.pos);
        SDL_BlitSurface(locked->image,NULL,screen,&locked->pos);
        SDL_BlitSurface(base3[0].image,NULL,screen,&base3[0].pos);
        SDL_BlitSurface(base3[1].image,NULL,screen,&base3[1].pos);
        SDL_BlitSurface(base3[2].image,NULL,screen,&base3[2].pos);
        SDL_BlitSurface(base2[0].image,NULL,screen,&base2[0].pos);
        SDL_BlitSurface(base2[1].image,NULL,screen,&base2[1].pos);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(screen);
}

int AffichageJeuSingleplayer(SDL_Surface* screen, Personnage player, Map map, Object* entity, HUD hud, keybinds *kb, NPC* npc,Background pauseBackground,Background settingsBackground, Button *button,Mix_Chunk *SoundButtonHover, Mix_Chunk *SoundButtonClick, Text txt){
  int done = 0, crushUp[3] = {1,0,1}, grabberState = 0, cp = 450, move = 1, timing = 2, rot = 6, angle1 = 0, angle2 = 0;
  int tempsPrec = 0, tempsAct = 0, tPr = 0, tAc = 0, oTime = 0, cTime = 135, startTimer = 0, doortimer = 2, nT = 60, oT = 2, noEnigme = 1;
  Map mapFile;
  SDL_Event event;
  SDL_Surface* rotation1 = rotozoomSurface(entity[17].src, angle1, 1.0, 1), * rotation2 = rotozoomSurface(entity[18].src, angle2, 1.0, 1);
  Uint8* keys;
  protocol base3[3],base2[2];
  SDL_Surface *pos3[4],*pos2[2],*unlocked,*lockked;
  simple image,circuit,locked;
  while(!done){
    entity[23].state = !player.inPresent;
    if(player.inPresent){
      SDL_BlitSurface(map.resetP, NULL, map.present, NULL);
    }else{
      SDL_BlitSurface(map.resetF, NULL, map.future, NULL);
    }
    afficherNPC(npc, &map);
    if(timing == 0){
      animerPersonnage(&player);
      timing = 2;
    }else{
      timing--;
    }
    afficherJoueur(player, map);
    afficherObjects(&map,entity, 0, 17, player, rotation1, rotation2);
    afficherMap(&screen, map, player);
    afficherHUD(&screen, &hud, player);
    SDL_Flip(screen);
    moveObjects(entity, crushUp, &grabberState, &move, &player, &map);
    if(noEnigme){
        if(player.currlvl == 1 && player.pos.x >= entity[8].pos.x - 300){
            initialiser(base3,base2,pos3,pos2,&unlocked,&lockked,&circuit,&locked,&image);
            if(afficher(screen,base3,base2,pos3,pos2,unlocked,lockked,circuit,&locked,event,image) == 1){
                noEnigme = 0;
                entity[8].spawn = 0;
            }
          }
      }
    if(oT == 0){
        animateObjects(entity);
        oT = 2;
    }else{
        oT--;
    }
    if(rot == 6){
        SDL_FreeSurface(rotation1);
        rotation1 = rotozoomSurface(entity[17].src, angle1, 1.0, 1);
        angle1 += 20;
        SDL_FreeSurface(rotation2);
        rotation2 = rotozoomSurface(entity[18].src, angle2, 1.0, 1);
        angle2 += 20;
    }
    SDL_PumpEvents();
    keys = SDL_GetKeyState(NULL);
    if(move){
      deplacerJoueur(&player, &map, entity, keys, *kb, npc);
    }
    deplacerNPCs(npc, map, &player);
    gravity(&player, &map, npc, move, entity);
    updateHUD(&player, &tempsPrec, &tempsAct, &hud);
    if(player.currlvl == 2 || player.currlvl == 3){
        if(doortimer == 0){
            if(player.currlvl == 2){
                if(entity[12].state == 0 && entity[12].oldState == 0){
                    if(startTimer == 0){
                        if(player.pos.x >= 320){
                            startTimer = 1;
                        }
                    }else{
                        if(cTime == 0){
                            entity[12].state = 1;
                            entity[12].oldState = 1;
                        }else{
                            cTime--;
                        }
                    }
                }
                if(entity[12].state == 1){
                    if(entity[12].pos.y > 174){
                        entity[12].pos.y--;
                    }else{
                        entity[12].state = 2;
                    }
                }
                if(entity[12].state == 2){
                    if(player.pos.x >= 2373 && player.pos.x <= 2502){
                        entity[12].state = 3;
                        entity[14].state = 3;
                        player.currlvl = 3;
                        player.pos.x = 191;
                        player.pos.y = 240;
                        map.resetP = IMG_Load("materials/maps/Level3.png");
                        map.present = IMG_Load("materials/maps/Level3.png");
                        map.collisionP = IMG_Load("materials/maps/Level3Collision.png");
                        map.resetF = IMG_Load("materials/maps/Level3Future.png");
                        map.future = IMG_Load("materials/maps/Level3Future.png");
                        map.collisionF = IMG_Load("materials/maps/Level3FutureCollision.png");
                        map.zoompos.x = 0;
                        resetScrolling(player, &map);
                        map.zoompos.w = map.present->w;
                        map.zoompos.h = map.present->h;
                    }
                }
            }else{
                if(player.currlvl == 3){
                    if(entity[14].state == 3){
                        if(entity[14].pos.y < 225){
                            entity[14].pos.y++;
                        }else{
                            entity[14].state = 0;
                            entity[20].state = 1;
                            entity[21].state = 1;
                            entity[22].state = 1;
                        }
                    }
                    if(entity[14].state == 0){
                        if(nT == 0){
                            entity[20].state = 0;
                            entity[21].state = 0;
                            entity[22].state = 0;
                            entity[15].state = 1;
                        }else{
                            nT--;
                        }
                    }
                    if(entity[15].state == 1){
                        if(entity[15].pos.y > 110){
                            entity[15].pos.y--;
                        }else{
                            entity[15].state = 2;
                        }
                    }
                    if(entity[15].state == 2){
                        if(player.pos.x > entity[15].pos.x + 100){
                            entity[15].state = 3;
                        }
                    }
                    if(entity[15].state == 3){
                        if(entity[15].pos.y < 225){
                            entity[15].pos.y++;
                        }else{
                            entity[15].state = 0;
                        }
                    }
                }
            }
            doortimer = 2;
        }else{
            doortimer--;
        }
    }
    if(collisionDeath(player, map)){
        player.hp -= 100;
    }
    tAc = SDL_GetTicks();
    if(player.currlvl == 1){
        if(entity[19].state == 0){
            if(tAc - tPr > 3000){
                tPr = tAc;
                entity[19].state = 1;
            }
        }
        if(entity[19].state == 1){
            if(tAc - tPr > 500){
                tPr = tAc;
                entity[19].state = 2;
            }
        }
        if(entity[19].state == 2){
            if(tAc - tPr > 3000){
                tPr = tAc;
                entity[19].state = 3;
            }
        }
        if(entity[19].state == 3){
            if(tAc - tPr > 500){
                tPr = tAc;
                entity[19].state = 0;
            }
        }
        if(entity[19].state != 0 && player.pos.x >= 1229 && player.pos.x <= 1351){
            player.hp--;
        }
    }
    if(move && entity[10].state == 0){
        if(player.pos.x >= 3455 && player.pos.x <= 3532){
            move = 0;
            player.pos.y -= 10;
            entity[10].state = 1;
        }
    }
    if(entity[10].state == 1){
        if(entity[10].pos.y > 283){
            entity[10].pos.y -= 5;
            player.pos.y -= 5;
            resetScrolling(player, &map);
        }else{
            entity[10].state = 2;
            move = 1;
            player.currlvl = 2;
            player.pos.x = 73;
            player.pos.y = 311;
            SDL_FreeSurface(map.present);
            SDL_FreeSurface(map.collisionP);
            SDL_FreeSurface(map.resetP);
            map.present = IMG_Load("materials/maps/Level2.png");
            map.collisionP = IMG_Load("materials/maps/Level2Collision.png");
            map.resetP = IMG_Load("materials/maps/Level2.png");
            map.zoompos.x = 0;
            resetScrolling(player, &map);
            map.zoompos.w = map.present->w;
            map.zoompos.h = map.present->h;
        }
    }
    if(collisionChangeMap(player, map)){
        SDL_FreeSurface(map.collisionP);
        SDL_FreeSurface(map.present);
        SDL_FreeSurface(map.collisionF);
        SDL_FreeSurface(map.future);
        SDL_FreeSurface(map.resetP);
        SDL_FreeSurface(map.resetF);
        if(player.inPresent){
            if(player.currlvl == 3){
                player.currlvl = 4;
                player.pos.x = 266;
                player.pos.y = 302;
                map.resetP = IMG_Load("materials/maps/Level4.png");
                map.present = IMG_Load("materials/maps/Level4.png");
                map.collisionP = IMG_Load("materials/maps/Level4Collision.png");
                map.resetF = IMG_Load("materials/maps/Level4Future.png");
                map.future = IMG_Load("materials/maps/Level4Future.png");
                map.collisionF = IMG_Load("materials/maps/Level4FutureCollision.png");
                map.zoompos.x = 0;
                resetScrolling(player, &map);
                map.zoompos.w = map.present->w;
                map.zoompos.h = map.present->h;
            }else{
                if(player.currlvl == 4){
                    player.currlvl = 3;
                    player.pos.y = 273;
                    map.resetP = IMG_Load("materials/maps/Level3.png");
                    map.present = IMG_Load("materials/maps/Level3.png");
                    map.collisionP = IMG_Load("materials/maps/Level3Collision.png");
                    map.future = IMG_Load("materials/maps/Level3Future.png");
                    map.resetF = IMG_Load("materials/maps/Level3Future.png");
                    map.collisionF = IMG_Load("materials/maps/Level3FutureCollision.png");
                    map.zoompos.x = map.present->w - 580;
                    resetScrolling(player, &map);
                    map.zoompos.w = map.present->w;
                    map.zoompos.h = map.present->h;
                    player.pos.x = map.present->w - 350;
                }
            }
        }else{
            if(player.currlvl == 3){
                player.currlvl = 4;
                player.pos.x = 266;
                player.pos.y = 302;
                map.resetF = IMG_Load("materials/maps/Level4Future.png");
                map.future = IMG_Load("materials/maps/Level4Future.png");
                map.collisionF = IMG_Load("materials/maps/Level4FutureCollision.png");
                map.present = IMG_Load("materials/maps/Level4.png");
                map.resetP = IMG_Load("materials/maps/Level4.png");
                map.collisionP = IMG_Load("materials/maps/Level4Collision.png");
                map.zoompos.x = 0;
                resetScrolling(player, &map);
                map.zoompos.w = map.future->w;
                map.zoompos.h = map.future->h;
            }else{
                if(player.currlvl == 4 && player.pos.x < map.future->w / 2){
                    player.currlvl = 3;
                    player.pos.y = 273;
                    map.resetF = IMG_Load("materials/maps/Level3Future.png");
                    map.future = IMG_Load("materials/maps/Level3Future.png");
                    map.collisionF = IMG_Load("materials/maps/Level3FutureCollision.png");
                    map.present = IMG_Load("materials/maps/Level3.png");
                    map.resetP = IMG_Load("materials/maps/Level3.png");
                    map.collisionP = IMG_Load("materials/maps/Level3Collision.png");
                    map.zoompos.x = map.present->w - 580;
                    resetScrolling(player, &map);
                    map.zoompos.w = map.future->w;
                    map.zoompos.h = map.future->h;
                    player.pos.x = map.present->w - 350;
                }else{
                    if(player.currlvl == 4 && player.pos.x > map.future->w / 2){
                        player.currlvl = 5;
                        player.pos.x = 120;
                        player.pos.y = 73;
                        map.resetF = IMG_Load("materials/maps/Level5Future.png");
                        map.future = IMG_Load("materials/maps/Level5Future.png");
                        map.collisionF = IMG_Load("materials/maps/Level5FutureCollision.png");
                        map.present = IMG_Load("materials/maps/Level5.png");
                        map.resetP = IMG_Load("materials/maps/Level5.png");
                        map.collisionP = IMG_Load("materials/maps/Level5Collision.png");
                        map.zoompos.x = 0;
                        resetScrolling(player, &map);
                        map.zoompos.w = map.future->w;
                        map.zoompos.h = map.future->h;
                    }else{
                        if(player.currlvl == 5){
                            player.currlvl = 4;
                            player.pos.x = 2165;
                            player.pos.y = 339;
                            map.resetF = IMG_Load("materials/maps/Level4Future.png");
                            map.future = IMG_Load("materials/maps/Level4Future.png");
                            map.collisionF = IMG_Load("materials/maps/Level4FutureCollision.png");
                            map.present = IMG_Load("materials/maps/Level4.png");
                            map.resetP = IMG_Load("materials/maps/Level4.png");
                            map.collisionP = IMG_Load("materials/maps/Level4Collision.png");
                            map.zoompos.x = 1965;
                            resetScrolling(player, &map);
                            map.zoompos.w = map.future->w;
                            map.zoompos.h = map.future->h;
                        }
                    }
                }
            }
        }
    }
    while( SDL_PollEvent( &event ) ){
      switch( event.type ){
        case SDL_KEYUP:
            if(event.key.keysym.sym == kb->swaptime){
                if(player.currlvl > 2){
                   player.inPresent = !player.inPresent;
                   player.pos.y -= 26;
               }
            }
            break;
        case SDL_KEYDOWN:
          if(event.key.keysym.sym == SDLK_ESCAPE){
            gamePause(&done,map,hud,player,screen,entity,npc,kb,pauseBackground,settingsBackground,button, SoundButtonHover, SoundButtonClick, txt);
          }
          break;
      }
    }
    if(player.hp <= 0){
      player.vie--;
      if(player.vie == 0){
        //gameover();
      }else{
          player.hp = 100;
          restartCheckpoint(&player, &map);
      }
    }
  }
  if(rot == 0){
      rot = 6;
  }else{
      rot--;
  }
}

void loadgame(Personnage* player, Map *map, Object* entity, HUD *hud, NPC* npc){
  FILE *f = fopen("saves/continue.save", "rb");
  if(f != NULL){
    fread(map, sizeof(Map), 1, f);
    fread(player, sizeof(Personnage), 1, f);
    fread(entity, sizeof(Object), 24, f);
    fread(npc, sizeof(NPC), 10, f);
    fclose(f);
  }
}
void jeuSingleplayer(SDL_Surface* screen, Button *button, keybinds *kb,Mix_Chunk *SoundButtonHover, Mix_Chunk *SoundButtonClick, Text txt, int newgame){
    Personnage player;
    Map map;
    Object entity[25];
    HUD hud;
    NPC npc[10];
    Background pauseBackground,settingsBackground;
    pauseBackground.src = IMG_Load("materials/HUD/GamePause/pauseBackground.png");
  	if(pauseBackground.src == NULL){
  		printf("Unable to load Game Pause Menu File: %s\n", SDL_GetError());
  		exit(EXIT_FAILURE);
  	}
    pauseBackground.pos.x = 148;
  	pauseBackground.pos.y = 81;

    settingsBackground.src = IMG_Load("materials/menu/Settings/settingsBackground.png");
  	if(settingsBackground.src == NULL){
  		printf("Unable to load Game Pause Menu File: %s\n", SDL_GetError());
  		exit(EXIT_FAILURE);
  	}
    settingsBackground.pos.x = 148;
  	settingsBackground.pos.y = 81;
    if(newgame){
      initSinglePlayer(&player, &map, entity, &hud, npc);
    }else{
      loadgame(&player, &map, entity, &hud, npc);
      initImages(&player, &map, entity, &hud, npc);
    }
    int done = AffichageJeuSingleplayer(screen, player, map, entity, hud, kb, npc, pauseBackground, settingsBackground, button, SoundButtonHover, SoundButtonClick, txt);
    /*if(done){
      credits;
    }*/
}
