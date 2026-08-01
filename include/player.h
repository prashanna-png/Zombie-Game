#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct
{
  SDL_Rect rect;

  int speed;

  SDL_bool movingUp;
  SDL_bool movingDown;
  SDL_bool movingLeft;
  SDL_bool movingRight;

} Player;

void initPlayer(Player *player);
void drawPlayer(Player *player, SDL_Renderer *renderer);
void updatePlayer(Player *player);

#endif