#include "zombie.h"
#include <SDL2/SDL_image.h>

void initZombie(Zombie *zombie, SDL_Renderer *renderer)
{
  zombie->rect.x = 400;
  zombie->rect.y = 300;
  zombie->rect.w = 50;
  zombie->rect.h = 40;
  zombie->speed = 2;
  zombie->health = 100;
  zombie->alive = SDL_TRUE;

  zombie->texture = IMG_LoadTexture(renderer, "assets/zombie/zombie.png");

  if (!zombie->texture)
  {
    printf("Failed to load texture: %s\n", IMG_GetError());
  }
}

void drawZombie(Zombie *zombie, SDL_Renderer *renderer)
{
  if (zombie->alive == SDL_TRUE)
  {
    SDL_RenderCopy(renderer, zombie->texture, NULL, &zombie->rect);
  }
}