#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL2/SDL.h>
#include <utils.h>

typedef enum {
  ASTEROID_SIZE_BIG,
  ASTEROID_SIZE_MEDIUM,
  ASTEROID_SIZE_SMALL,
} asteroid_size;

typedef struct {
  asteroid_size size;
  double angle;
  SDL_Rect position;
  SDL_Texture *texture;
} asteroid_t;

asteroid_t asteroid_create(SDL_Renderer *renderer);
void asteroid_render(asteroid_t *asteroid, SDL_Renderer *renderer);
void asteroid_update(asteroid_t *asteroid, float delta_time);

#endif
