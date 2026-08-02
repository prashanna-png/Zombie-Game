#include "player.h"
#include <SDL2/SDL_image.h>

void initPlayer(Player *player, SDL_Renderer *renderer)
{

  player->rect.x = 100;
  player->rect.y = 100;
  player->rect.w = 30;
  player->rect.h = 30;
  player->speed = 4;
  player->movingUp = SDL_FALSE;
  player->movingDown = SDL_FALSE;
  player->movingLeft = SDL_FALSE;
  player->movingRight = SDL_FALSE;

  player->texture = IMG_LoadTexture(renderer, "assets/player/player-stand.png");

  if (!player->texture)
  {
    printf("Failed to load texture: %s\n", IMG_GetError());
  }
}
void drawPlayer(Player *player, SDL_Renderer *renderer)
{
  SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
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
