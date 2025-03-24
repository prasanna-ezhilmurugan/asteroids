#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <asteroids.h>
#include <player.h>
#include <stdbool.h>

typedef enum { START, RUNNING, OVER, QUIT } game_state;

typedef struct {
  // rendering
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;

  // components
  player_t player;
  asteroid_t asteroids[ASTEROID_COUNT];

  // Textures
  SDL_Texture *start_screen;
  SDL_Texture *over_screen;

  // state
  int life;
  game_state state;

  // time
  float tick_count;
} game_t;

int initialize_game(game_t *game);
void quit_game(game_t *game);

void handle_event(game_t *game);
void render(game_t *game);
void update(game_t *game);

#endif
