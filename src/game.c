// Responsible for:
// Initialize SDL
// Create Window
// Create Renderer
// Game Loop
// Cleanup

#include <SDL2/SDL.h>
#include "game.h"
#include <stdio.h>

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

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = SDL_FALSE;
      }
    }

    SDL_SetRenderDrawColor(renderer, 100, 190, 130, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}