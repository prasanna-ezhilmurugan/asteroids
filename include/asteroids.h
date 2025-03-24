#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL2/SDL.h>
#include <utils.h>

#define ASTEROID_COUNT 5
#define ASTEROID_TEXTURES 3

typedef enum {
  ASTEROID_SIZE_BIG,
  ASTEROID_SIZE_MEDIUM,
  ASTEROID_SIZE_SMALL,
} asteroid_size;

static SDL_Texture *asteroid_texture[ASTEROID_TEXTURES] = {NULL};

typedef struct {
  bool alive;
  asteroid_size size;
  double angle;
  SDL_Rect position;
  SDL_Texture *texture;
} asteroid_t;

void asteroid_init(SDL_Renderer *renderer);
asteroid_t asteroid_create();
void asteroid_render(asteroid_t *asteroid, SDL_Renderer *renderer);
void asteroid_update(asteroid_t *asteroid, float delta_time);
void asteroid_destroy();

#endif
