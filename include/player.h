#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct
{
  SDL_Texture *texture;
  SDL_FRect rect;

  int speed;

  SDL_bool movingUp;
  SDL_bool movingDown;
  SDL_bool movingLeft;
  SDL_bool movingRight;

  int health;

} Player;

void initPlayer(Player *player, SDL_Renderer *renderer);
void drawPlayer(Player *player, SDL_Renderer *renderer);
void updatePlayer(Player *player);

#endif