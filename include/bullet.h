#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "player.h"

typedef struct
{
  SDL_FRect rect;

  float dx;
  float dy;

  float speed;

  SDL_Texture *texture;

  SDL_bool active;


} Bullet;

void initBullet(Bullet *bullet, SDL_Renderer *renderer);
void drawBullet(Bullet *bullet, SDL_Renderer *renderer);
void updateBullet(Bullet *bullet);
void fireBullet(Bullet *bullet, Player *player, int mouseX, int mouseY);

#endif