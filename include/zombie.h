#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <SDL2/SDL.h>

typedef struct
{
  SDL_Texture *texture;
  SDL_Rect rect;

  int speed;

  int health;

  SDL_bool alive;

} Zombie;

void initZombie(Zombie *zombie, SDL_Renderer *renderer);
void drawZombie(Zombie *zombie, SDL_Renderer *renderer);
void updateZombie(Zombie *zombie, SDL_Rect playerRect);

#endif