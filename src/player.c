#include "player.h"

void initPlayer(Player *player)
{
  player->rect.x = 100;
  player->rect.y = 100;
  player->rect.w = 50;
  player->rect.h = 50;
  player->speed = 4;
  player->movingUp = SDL_FALSE;
  player->movingDown = SDL_FALSE;
  player->movingLeft = SDL_FALSE;
  player->movingRight = SDL_FALSE;
}
void drawPlayer(Player *player, SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &player->rect);
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

  
}
