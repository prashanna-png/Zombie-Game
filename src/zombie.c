#include "zombie.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <math.h>

void initZombie(Zombie *zombie, SDL_Renderer *renderer)
{
  zombie->rect.x = 400;
  zombie->rect.y = 300;
  zombie->rect.w = 60;
  zombie->rect.h = 60;
  zombie->speed = 1;
  zombie->health = 100;
  zombie->alive = SDL_TRUE;
  zombie->lastAttackTime = 0;

  zombie->texture = IMG_LoadTexture(renderer, "assets/zombie/zombie.png");

  if (!zombie->texture)
  {
    printf("Failed to load texture: %s\n", IMG_GetError());
  }
}

void drawZombie(Zombie *zombie, SDL_Renderer *renderer)
{
  if (!zombie->alive)
  {
    return;
  }
  SDL_RenderCopyF(renderer, zombie->texture, NULL, &zombie->rect);
}

void updateZombie(Zombie *zombie, SDL_Rect playerRect)
{
  if (!zombie->alive)
  {
    return;
  }

  float playerCenterX = playerRect.x + playerRect.w / 2;
  float playerCenterY = playerRect.y + playerRect.h / 2;

  float zombieCenterX = zombie->rect.x + zombie->rect.w / 2;
  float zombieCenterY = zombie->rect.y + zombie->rect.h / 2;

  float dx = playerCenterX - zombieCenterX;
  float dy = playerCenterY - zombieCenterY;

  float length = sqrt(dx * dx + dy * dy);

  if (length != 0)
  {
    dx /= length;
    dy /= length;
  }

  zombie->rect.x += dx * zombie->speed;
  zombie->rect.y += dy * zombie->speed;
}
