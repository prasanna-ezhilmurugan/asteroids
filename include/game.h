#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <player.h>
#include <stdbool.h>

enum game_state { START, RUNNING, GAME_STATES };

typedef struct {
  // rendering
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;
  // textures
  player_t player;

  // state
  bool state[GAME_STATES];
} game_t;

bool initialize_game(game_t *game);
void quit_game(game_t *game);

void handle_event(game_t *game);
void render(game_t *game);
void update(game_t *game);

#endif