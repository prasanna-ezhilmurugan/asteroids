#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <player.h>
#include <stdbool.h>

typedef struct {
  // rendering
  SDL_Window *window;
  SDL_Renderer *renderer;

  // textures
  player_t player;

  // state
  bool is_running;
} game_t;

bool initialize_game(game_t *game);
void quit_game(game_t *game);

void handle_event(game_t *game);
void render(game_t *game);
void update(game_t *game);

#endif