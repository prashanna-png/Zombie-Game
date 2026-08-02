// Responsible for:
// Initialize SDL
// Create Window
// Create Renderer
// Game Loop
// Cleanup

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "game.h"
#include "player.h"
#include <stdio.h>
#include <math.h>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

void runGame(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    printf("SDL initialized succesfully\n");
  }
  else
  {
    printf("SDL Initialization Error: %s\n", SDL_GetError());
    return;
  }
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
    printf("SDL_image Initialization Error: %s\n", IMG_GetError());
    SDL_Quit();
    return;
  }

  window = SDL_CreateWindow(
      "Zombie Survival",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1024,
      768,
      SDL_WINDOW_SHOWN);

  if (!window)
  {
    printf("Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    return;
  }

  renderer = SDL_CreateRenderer(
      window,
      -1,
      SDL_RENDERER_ACCELERATED);

  if (!renderer)
  {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
  }

  SDL_bool running = SDL_TRUE;
  SDL_Event event;

  Player player;
  initPlayer(&player, renderer);

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = SDL_FALSE;
      }

      if (event.type == SDL_KEYDOWN)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
          player.movingUp = SDL_TRUE;
          break;
        case SDLK_s:
          player.movingDown = SDL_TRUE;
          break;
        case SDLK_a:
          player.movingLeft = SDL_TRUE;
          break;
        case SDLK_d:
          player.movingRight = SDL_TRUE;
          break;
        }
      }
      else if (event.type == SDL_KEYUP)
      {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
          player.movingUp = SDL_FALSE;
          break;
        case SDLK_s:
          player.movingDown = SDL_FALSE;
          break;
        case SDLK_a:
          player.movingLeft = SDL_FALSE;
          break;
        case SDLK_d:
          player.movingRight = SDL_FALSE;
          break;
        }
      }
    }

    updatePlayer(&player);
    

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    drawPlayer(&player, renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
