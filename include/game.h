#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <player.h>
#include <stdbool.h>

enum game_state { START, RUNNING, QUIT };

typedef struct {
  // rendering
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;

  player_t player;
  SDL_Texture *start_screen;

  // state
  int state;

  // time
  float tick_count;
} game_t;

int initialize_game(game_t *game);
void quit_game(game_t *game);

void handle_event(game_t *game);
void render(game_t *game);
void update(game_t *game);

#endif
