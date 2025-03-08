#include <SDL2/SDL_image.h>
#include <game.h>
#include <stdio.h>

SDL_Texture *load_texture(SDL_Renderer *renderer, char *path) {
  SDL_Texture *texture = NULL;
  SDL_Surface *surface = IMG_Load(path);
  if (!surface) {
    fprintf(stderr, "error: cannot load image %s SDL_Image: %s\n", path,
            IMG_GetError());
  } else {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
      fprintf(stderr, "error: cannot create texture from %s SDL_Image: %s\n",
              path, SDL_GetError());
    }
    SDL_FreeSurface(surface);
  }
  return texture;
}

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

  // load texture
  game->texture = load_texture(game->renderer, "assets/sprite-sheet.png");
  if (!game->texture) {
    return false;
  }

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

  SDL_RenderCopy(game->renderer, game->texture, NULL, NULL);

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
  if (game->texture) {
    SDL_DestroyTexture(game->texture);
    game->texture = NULL;
  }
  SDL_Quit();
}