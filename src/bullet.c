#include <SDL2/SDL.h>
#include "bullet.h"
#include "player.h"
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

void fireBullet(Bullet *bullet, Player *player, int mouseX, int mouseY)
{
  bullet->active = SDL_TRUE;

  float centerX = player->rect.x + player->rect.w / 2.0f;
  float centerY = player->rect.y + player->rect.h / 2.0f;

  bullet->rect.x = centerX - bullet->rect.w / 2.0f;
  bullet->rect.y = centerY - bullet->rect.h / 2.0f;

  SDL_GetMouseState(&mouseX, &mouseY);

  bullet->dy = mouseY - centerY;
  bullet->dx = mouseX - centerX;

  float length = sqrt(bullet->dx * bullet->dx + bullet->dy * bullet->dy);

  if (length != 0)
  {
    bullet->dx /= length;
    bullet->dy /= length;
  }
}