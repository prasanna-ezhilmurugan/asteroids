#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_TITLE "asteroids"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

typedef struct {
  // rendering
  SDL_Window *window;
  SDL_Renderer *renderer;

  // textures
  SDL_Texture *texture;

  // state
  bool is_running;
} game_t;

bool initialize_game(game_t *game);
void quit_game(game_t *game);

void handle_event(game_t *game);
void render(game_t *game);

#endif