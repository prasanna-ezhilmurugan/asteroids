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
  SDL_Texture *start_screen_texture;
  SDL_Rect start_screen_rect;
  SDL_Texture *over_screen_texture;
  SDL_Rect over_screen_rect;

  // score
  SDL_Texture *score_texture;
  SDL_Rect score_rect;
  int score;
  char score_string[20];

  // state
  int life;
  game_state state;

  // time
  float tick_count;
} game_t;

bool load_game(game_t *game);
void init_game(game_t *game);
void quit_game(game_t *game);

void handle_event(game_t *game);
void render(game_t *game);
void update(game_t *game);

#endif
