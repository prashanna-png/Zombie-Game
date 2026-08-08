#include "player.h"
#include <SDL2/SDL_image.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void initPlayer(Player *player, SDL_Renderer *renderer)
{

  player->rect.x = 100;
  player->rect.y = 100;
  player->rect.w = 70;
  player->rect.h = 60;
  player->speed = 3;
  player->movingUp = SDL_FALSE;
  player->movingDown = SDL_FALSE;
  player->movingLeft = SDL_FALSE;
  player->movingRight = SDL_FALSE;
  player->health = 100;

  player->texture = IMG_LoadTexture(renderer, "assets/player/player-stand.png");

  if (!player->texture)
  {
    printf("Failed to load texture: %s\n", IMG_GetError());
  }
}

void drawPlayer(Player *player, SDL_Renderer *renderer)
{

  int mouseX;
  int mouseY;

  SDL_GetMouseState(&mouseX, &mouseY);

  float centerX = player->rect.x + player->rect.w / 2.0f;
  float centerY = player->rect.y + player->rect.h / 2.0f;

  float dy = mouseY - centerY;
  float dx = mouseX - centerX;

  float angleRadians = atan2(dy, dx);
  float angleDegrees = angleRadians * (180.0f / M_PI);

  SDL_FPoint center = {
      player->rect.w / 2.0f,
      player->rect.h / 2.0f};

  SDL_RenderCopyExF(
      renderer,
      player->texture,
      NULL,
      &player->rect,
      angleDegrees,
      &center,
      SDL_FLIP_VERTICAL);
}

void updatePlayer(Player *player)
{
  if (player->movingUp == SDL_TRUE)
  {
    player->rect.y -= player->speed;
  }
  if (player->movingDown == SDL_TRUE)
  {
    player->rect.y += player->speed;
  }
  if (player->movingLeft == SDL_TRUE)
  {
    player->rect.x -= player->speed;
  }
  if (player->movingRight == SDL_TRUE)
  {
    player->rect.x += player->speed;
  }

  if (player->rect.x < 0)
  {
    player->rect.x = 0;
  }
  if (player->rect.x > 1024 - player->rect.w)
  {
    player->rect.x = 1024 - player->rect.w;
  }
  if (player->rect.y < 0)
  {
    player->rect.y = 0;
  }
  if (player->rect.y > 768 - player->rect.h)
  {
    player->rect.y = 768 - player->rect.h;
  }
}
