#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
  SDL_Texture *texture;
  // props
  float dx, dy;

  SDL_Rect position;

} player_t;

player_t player_create(SDL_Renderer *renderer, const char *path);
void player_render(player_t *player, SDL_Renderer *renderer);
void player_handle_event(player_t *player, SDL_Event *event);
void player_update(player_t *player);
void player_destroy(player_t *player);

#endif