#include <SDL2/SDL_image.h>
#include <game.h>
#include <stdio.h>
#include <utils.h>

bool initialize_game(game_t *game) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "error: cannot initialize SDL: %s\n", SDL_GetError());
    return false;
  }

  // create window or throw
  game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!game->window) {
    fprintf(stderr, "error: cannot create SDL window: %s\n", SDL_GetError());
    return false;
  }

  // create renderer or throw
  game->renderer = SDL_CreateRenderer(
      game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!game->renderer) {
    fprintf(stderr, "error: cannot create SDL renderer: %s\n", SDL_GetError());
    return false;
  }

  // initialize SDL_Image
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    fprintf(stderr, "error: cannot initialize SDL image: %s\n", IMG_GetError());
    return false;
  }

  game->player = player_create(game->renderer, "assets/player.png");

  return true;
}

void handle_event(game_t *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      game->is_running = false;
    }
  }
}

void render(game_t *game) {
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);

  player_render(&game->player, game->renderer);

  SDL_RenderPresent(game->renderer);
}

void quit_game(game_t *game) {
  if (game->window) {
    SDL_DestroyWindow(game->window);
    game->window = NULL;
  }
  if (game->renderer) {
    SDL_DestroyRenderer(game->renderer);
    game->renderer = NULL;
  }
  player_destroy(&game->player);
  SDL_Quit();
}