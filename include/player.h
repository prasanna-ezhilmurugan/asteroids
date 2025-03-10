#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL_render.h>

typedef struct {
  SDL_Texture *texture;
  // props
  float x, y;
  float dx, dy;

} player_t;

player_t player_create(SDL_Renderer *renderer, const char *path);
void player_render(player_t *player, SDL_Renderer *renderer);
void player_destroy(player_t *player);

#endif