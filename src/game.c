// Responsible for:
// Initialize SDL
// Create Window
// Create Renderer
// Game Loop
// Cleanup

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#include "game.h"
#include "player.h"
#include "bullet.h"
#include "zombie.h"

#define MAX_BULLETS 100
#define MAX_ZOMBIES 20

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *backgroundTexture = NULL;

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

  backgroundTexture = IMG_LoadTexture(renderer, "assets/map/background.jpg");

  if (!backgroundTexture)
  {
    printf("Failed to load background texture: %s\n", IMG_GetError());
  }
  else
  {
    printf("Background texture loaded successfully\n");
  }

  if (!renderer)
  {
    printf("Renderer creation failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return;
  }
  else
  {
    printf("Renderer created successfully\n");
  }

  SDL_bool running = SDL_TRUE;
  SDL_Event event;

  Player player;
  initPlayer(&player, renderer);

  Bullet bullet[MAX_BULLETS];
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    initBullet(&bullet[i], renderer);
  }

  Zombie zombie[MAX_ZOMBIES];
  for (int i = 0; i < MAX_ZOMBIES; i++)
  {
    initZombie(&zombie[i], renderer);
  }

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

      if (event.type == SDL_MOUSEBUTTONDOWN)
      {
        if (event.button.button == SDL_BUTTON_LEFT)
        {
          int mouseX, mouseY;
          SDL_GetMouseState(&mouseX, &mouseY);

          for (int i = 0; i < MAX_BULLETS; i++)
          {
            if (bullet[i].active == SDL_FALSE)
            {
              fireBullet(&bullet[i], &player, mouseX, mouseY);
              break;
            }
          }
        }
      }
    }

    updatePlayer(&player);

    for (int i = 0; i < MAX_ZOMBIES; i++)
    {
      updateZombie(&zombie[i], player.rect);
    }

    for (int i = 0; i < MAX_BULLETS; i++)
    {
      updateBullet(&bullet[i]);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    if (backgroundTexture)
    {
      SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    for (int i = 0; i < MAX_ZOMBIES; i++)
    {
      drawZombie(&zombie[i], renderer);
    }

    drawPlayer(&player, renderer);
    for (int i = 0; i < MAX_BULLETS; i++)
    {
      drawBullet(&bullet[i], renderer);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(16);
  }
  if (backgroundTexture)
  {
    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = NULL;
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
