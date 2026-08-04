#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>

typedef struct
{
  SDL_FRect rect;

  float dx;
  float dy;

  float speed;

  SDL_Texture *texture;

  SDL_bool active;

} Bullet;

#endif