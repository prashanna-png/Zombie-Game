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

void runGame(void)
{
  if (SDL_Init(SDL_INIT_VIDEO) == 0)
  {
    printf("SDL initialized succesfully\n");
    // Remove the return here - let it continue
  }
  else
  {
    printf("SDL Initialization Error: %s\n", SDL_GetError());
    return; // Keep this return - initialization failed
  }

  window = SDL_CreateWindow(
      "Zombie Survival",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      800,
      600,
      SDL_WINDOW_SHOWN);

  if (!window)
  {
    printf("Window creation failed: %s\n", SDL_GetError());
    SDL_Quit();
    return;
  }

  // You need a game loop here
  int running = 1;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
        running = 0;
    }
    // Render stuff here later
  }

  SDL_DestroyWindow(window);
  SDL_Quit();
}