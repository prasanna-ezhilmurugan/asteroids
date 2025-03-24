#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

enum player_directions { eUp, eDown, eLeft, eRight, eNumDirections };

typedef struct {
  SDL_Texture *texture;
  // props
  float angle;

  SDL_Rect position;

  bool directions[eNumDirections];
} player_t;

player_t player_create(SDL_Renderer *renderer, const char *path);
void player_render(player_t *player, SDL_Renderer *renderer);
void player_handle_event(player_t *player, SDL_Event *event);
void player_update(player_t *player, float delta_time);
void player_destroy(player_t *player);

#endif
