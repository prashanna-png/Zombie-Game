#include "player.h"

void initPlayer(Player *player)
{
  player->rect.x = 100;
  player->rect.y = 100;
  player->rect.w = 50;
  player->rect.h = 50;
}
void drawPlayer(Player *player, SDL_Renderer *renderer)
{
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &player->rect);
}

void updatePlayer(Player *player)
{
  player->rect.x += 1; // Move the player to the right for demonstration
}
