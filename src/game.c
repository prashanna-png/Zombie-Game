// Responsible for:
// Initialize SDL
// Create Window
// Create Renderer
// Game Loop
// Cleanup

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

#include "game.h"
#include "player.h"
#include "bullet.h"
#include "zombie.h"

#define MAX_BULLETS 100
#define MAX_ZOMBIES 20
#define ZOMBIE_SPAWN_INTERVAL 50

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *backgroundTexture = NULL;

int getZombieSpeed(int kills)
{
  if (kills >= 70)
    return 3;
  else if (kills >= 50)
    return 2;
  else
    return 1;
}
void drawAmmo(SDL_Renderer *renderer, TTF_Font *font, int ammo, int maxAmmo)
{
  char text[50];
  snprintf(text, sizeof(text), "Ammo: %d / %d", ammo, maxAmmo);

  SDL_Color white = {255, 255, 255, 255};

  SDL_Surface *surface = TTF_RenderText_Solid(
      font,
      text,
      white);

  if (!surface)
  {
    printf("failed to create ammo text surface: %s\n", TTF_GetError());
    return;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(
      renderer,
      surface);

  if (!texture)
  {
    printf("failed to create ammo text texture: %s\n", SDL_GetError());
    SDL_FreeSurface(surface);
    return;
  }

  SDL_FRect textRect;

  textRect.x = 20;
  textRect.y = 80;
  textRect.w = surface->w;
  textRect.h = surface->h;

  SDL_RenderCopyF(renderer, texture, NULL, &textRect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}
void spawnZombie(Zombie *zombie, SDL_Renderer *renderer)
{
  int side = rand() % 4;

  initZombie(zombie, renderer);

  switch (side)
  {
  case 0:
    zombie->rect.x = rand() % (1024 - (int)zombie->rect.w);
    zombie->rect.y = -zombie->rect.h;
    break;

  case 1:
    zombie->rect.x = rand() % (1024 - (int)zombie->rect.w);
    zombie->rect.y = 768;
    break;

  case 2:
    zombie->rect.x = -zombie->rect.w;
    zombie->rect.y = rand() % (768 - (int)zombie->rect.h);
    break;

  case 3:
    zombie->rect.x = 1024;
    zombie->rect.y = rand() % (768 - (int)zombie->rect.h);
    break;
  }
}
void drawHealthBar(SDL_Renderer *renderer, Player *player)
{
  SDL_FRect background;
  background.x = 20;
  background.y = 20;
  background.w = 200;
  background.h = 20;

  SDL_SetRenderDrawColor(renderer, 70, 70, 70, 255);
  SDL_RenderFillRectF(renderer, &background);

  SDL_FRect foreground;
  foreground.x = background.x;
  foreground.y = background.y;
  foreground.w = (player->health / 100.0f) * 200;
  foreground.h = background.h;

  if (player->health >= 70)
  {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
  }
  else if (player->health >= 30)
  {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Yellow
  }
  else
  {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
  }
  SDL_RenderFillRectF(renderer, &foreground);
}

void drawKills(SDL_Renderer *renderer, TTF_Font *font, int kills)
{
  if (!font)
  {
    return;
  }

  char text[50];
  snprintf(text, sizeof(text), "Kills: %d", kills);

  SDL_Color white = {0, 0, 0, 255};

  SDL_Surface *surface = TTF_RenderText_Solid(
      font,
      text,
      white);

  if (!surface)
  {
    printf("failed to create text surface: %s\n", TTF_GetError());
    return;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(
      renderer,
      surface);

  if (!texture)
  {
    printf("failed to create text texture: %s\n", SDL_GetError());
    SDL_FreeSurface(surface);
    return;
  }

  SDL_FRect textRect;

  textRect.x = 20;
  textRect.y = 50;
  textRect.w = surface->w;
  textRect.h = surface->h;

  SDL_RenderCopyF(renderer, texture, NULL, &textRect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}

void drawGameOver(SDL_Renderer *renderer, TTF_Font *font, int kill)
{
  if (!font)
  {
    return;
  }

  SDL_Color black = {0, 0, 0, 255};

  SDL_Surface *surface = TTF_RenderText_Solid(
      font,
      "Game Over",
      black);

  if (!surface)
  {
    printf("failed to create text surface: %s\n", TTF_GetError());
    return;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(
      renderer,
      surface);

  if (!texture)
  {
    printf("failed to create text texture: %s\n", SDL_GetError());
    SDL_FreeSurface(surface);
    return;
  }

  SDL_FRect textRect;

  textRect.w = surface->w;
  textRect.h = surface->h;

  textRect.x = (1024 - textRect.w) / 2.0f;
  textRect.y = 250;

  SDL_RenderCopyF(renderer, texture, NULL, &textRect);

  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);

  char killText[50];
  snprintf(killText, sizeof(killText), "Kills: %d", kill);

  SDL_Surface *killSurface = TTF_RenderText_Solid(
      font,
      killText,
      black);

  if (!killSurface)
  {
    printf("failed to create kill text surface: %s \n", TTF_GetError());
    return;
  }

  SDL_Texture *killTexture = SDL_CreateTextureFromSurface(
      renderer,
      killSurface);

  if (!killTexture)
  {
    printf("failed to create text texture: %s\n", SDL_GetError());
    SDL_FreeSurface(killSurface);
    return;
  }

  SDL_FRect killTextRect;

  killTextRect.w = killSurface->w;
  killTextRect.h = killSurface->h;

  killTextRect.x = (1024 - killTextRect.w) / 2.0f;
  killTextRect.y = 290;

  SDL_RenderCopyF(renderer, killTexture, NULL, &killTextRect);
  SDL_DestroyTexture(killTexture);
  SDL_FreeSurface(killSurface);
}

void runGame(void)

{
  srand(time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    printf("SDL Initialization Error: %s\n", SDL_GetError());
    return;
  }

  printf("SDL initialized successfully\n");

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
    printf("SDL_image Initialization Error: %s\n", IMG_GetError());
    SDL_Quit();
    return;
  }

  if (TTF_Init() != 0)
  {
    printf("SDL_ttf Initialization Error: %s\n", TTF_GetError());
    IMG_Quit();
    SDL_Quit();
    return;
  }

  window = SDL_CreateWindow(
      "Zombie Survival",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1024,
      768,
      SDL_WINDOW_RESIZABLE);

  if (!window)
  {
    printf("Window creation failed: %s\n", SDL_GetError());
    IMG_Quit();
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
    IMG_Quit();
    SDL_Quit();
    return;
  }

  printf("Renderer created successfully\n");

  backgroundTexture = IMG_LoadTexture(renderer, "assets/map/backgroundtry.jpeg");

  if (!backgroundTexture)
  {
    printf("Failed to load background texture: %s\n", IMG_GetError());
  }
  else
  {
    printf("Background texture loaded successfully\n");
  }

  TTF_Font *font = TTF_OpenFont("assets/fonts/Pixeled.ttf", 24);

  if (!font)
  {
    printf("failed to load font: %s\n", TTF_GetError());
  }

  SDL_bool running = SDL_TRUE;
  SDL_bool gameOver = SDL_FALSE;
  SDL_Event event;

  Player player;
  initPlayer(&player, renderer);

  int kill = 0;

  int ammo = 70;
  int maxAmmo = 70;

  Bullet bullet[MAX_BULLETS];
  for (int i = 0; i < MAX_BULLETS; i++)
  {
    initBullet(&bullet[i], renderer);
  }

  Zombie zombie[MAX_ZOMBIES];
  for (int i = 0; i < MAX_ZOMBIES; i++)
  {
    initZombie(&zombie[i], renderer);
    zombie[i].alive = SDL_FALSE;
  }

  Uint32 lastSpawnTime = SDL_GetTicks();

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

        case SDLK_r:
          if (gameOver)
          {
            player.health = 100;

            kill = 0;

            player.movingUp = SDL_FALSE;
            player.movingDown = SDL_FALSE;
            player.movingLeft = SDL_FALSE;
            player.movingRight = SDL_FALSE;

            player.rect.x = 100;
            player.rect.y = 100;

            ammo = 0;
            maxAmmo = 0;

            for (int i = 0; i < MAX_ZOMBIES; i++)
            {
              zombie[i].alive = SDL_FALSE;
            }

            for (int i = 0; i < MAX_BULLETS; i++)
            {
              bullet[i].active = SDL_FALSE;
            }

            gameOver = SDL_FALSE;
          }
          break;

        case SDLK_ESCAPE:
          running = SDL_FALSE;
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

      if (event.button.button == SDL_BUTTON_LEFT)
      {
        if (ammo > 0)
        {
          int mouseX, mouseY;
          SDL_GetMouseState(&mouseX, &mouseY);

          for (int i = 0; i < MAX_BULLETS; i++)
          {
            if (!bullet[i].active)
            {
              fireBullet(&bullet[i], &player, mouseX, mouseY);
              ammo--;
              break;
            }
          }
        }
      }
      if (event.button.button == SDL_BUTTON_RIGHT)
      {
        if (ammo < maxAmmo)
        {
          ammo = maxAmmo;
        }
      }
    }

    if (!gameOver)
    {
      updatePlayer(&player);

      Uint32 currentTime = SDL_GetTicks();

      if (currentTime - lastSpawnTime >= ZOMBIE_SPAWN_INTERVAL)
      {
        for (int i = 0; i < MAX_ZOMBIES; i++)
        {
          if (!zombie[i].alive && currentTime >= zombie[i].respawnTime)
          {
            spawnZombie(&zombie[i], renderer);
            zombie[i].speed = getZombieSpeed(kill);
            lastSpawnTime = currentTime;
            break;
          }
        }
      }

      for (int i = 0; i < MAX_ZOMBIES; i++)
      {
        updateZombie(&zombie[i], player.rect);
      }
      for (int i = 0; i < MAX_ZOMBIES; i++)
      {
        if (!zombie[i].alive)
          continue;

        for (int j = i + 1; j < MAX_ZOMBIES; j++)
        {
          if (!zombie[j].alive)
            continue;

          if (SDL_HasIntersectionF(&zombie[i].rect, &zombie[j].rect))
          {
            if (zombie[i].rect.x < zombie[j].rect.x)
            {
              zombie[j].rect.x += 1;
            }
            else
            {
              zombie[j].rect.x -= 1;
            }

            if (zombie[i].rect.y < zombie[j].rect.y)
            {
              zombie[j].rect.y += 1;
            }
            else
            {
              zombie[j].rect.y -= 1;
            }
          }
        }
      }

      for (int i = 0; i < MAX_BULLETS; i++)
      {
        updateBullet(&bullet[i]);
      }

      for (int i = 0; i < MAX_BULLETS; i++)
      {
        if (!bullet[i].active)
          continue;

        for (int j = 0; j < MAX_ZOMBIES; j++)
        {
          if (!zombie[j].alive)
            continue;

          if (SDL_HasIntersectionF(&bullet[i].rect, &zombie[j].rect))
          {
            zombie[j].health -= 35;
            bullet[i].active = SDL_FALSE;

            if (zombie[j].health <= 0)
            {
              zombie[j].alive = SDL_FALSE;
              zombie[j].respawnTime = currentTime + 2000;

              kill++;
            }

            break;
          }
        }
      }

      currentTime = SDL_GetTicks();

      for (int i = 0; i < MAX_ZOMBIES; i++)
      {
        if (!zombie[i].alive)
          continue;

        if (SDL_HasIntersectionF(&zombie[i].rect, &player.rect))
        {
          if (currentTime - zombie[i].lastAttackTime >= 1000)
          {
            player.health -= 10;

            if (player.health < 0)
            {
              player.health = 0;
            }

            zombie[i].lastAttackTime = currentTime;
          }
        }
      }

      if (player.health <= 0)
      {
        player.health = 0;
        gameOver = SDL_TRUE;
      }
    }

    SDL_RenderClear(renderer);

    if (backgroundTexture)
    {
      SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    }

    for (int i = 0; i < MAX_ZOMBIES; i++)
    {
      drawZombie(&zombie[i], renderer);
      drawZombieHealthBar(&zombie[i], renderer);
    }

    drawPlayer(&player, renderer);

    for (int i = 0; i < MAX_BULLETS; i++)
    {
      drawBullet(&bullet[i], renderer);
    }

    drawHealthBar(renderer, &player);
    drawKills(renderer, font, kill);
    drawAmmo(renderer, font, ammo, maxAmmo);

    if (gameOver)
    {
      drawGameOver(renderer, font, kill);
    }

    SDL_RenderPresent(renderer);

    SDL_Delay(16);
  }

  if (backgroundTexture)
  {
    SDL_DestroyTexture(backgroundTexture);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  TTF_CloseFont(font);
  TTF_Quit();

  IMG_Quit();
  SDL_Quit();
}