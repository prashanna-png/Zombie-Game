#include <SDL2/SDL.h>
#include "bullet.h"
#include <math.h>

void initBullet(Bullet *bullet, SDL_Renderer *renderer)
{

  bullet->active = SDL_FALSE;
  bullet->speed = 10;

  bullet->rect.w = 10.0f;
  bullet->rect.h = 7.0f;
}

void drawBullet(Bullet *bullet, SDL_Renderer *renderer)
{
  if (bullet->active == SDL_FALSE)
  {
    return;
  }
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRectF(renderer, &bullet->rect);
}

void updateBullet(Bullet *bullet)
{
  if (bullet->active == SDL_FALSE)
  {
    return;
  }

  bullet->rect.x += bullet->dx * bullet->speed;
  bullet->rect.y += bullet->dy * bullet->speed;

  if (bullet->rect.x < 0 ||
      bullet->rect.x > 1024 ||
      bullet->rect.y < 0 ||
      bullet->rect.y > 768)
  {
    bullet->active = SDL_FALSE;
  }
}

void fireBullet(Bullet *bullet, float startX, float startY, float targetX, float targetY)
{
  bullet->rect.x = startX;
  bullet->rect.y = startY;

  float dx = targetX - startX;
  float dy = targetY - startY;
  float length = sqrtf(dx * dx + dy * dy);

  if (length != 0)
  {
    bullet->dx = dx / length;
    bullet->dy = dy / length;
  }
  else
  {
    bullet->dx = 0;
    bullet->dy = 0;
  }

  bullet->active = SDL_TRUE;
}