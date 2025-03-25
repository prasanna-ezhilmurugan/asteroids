#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SDL2/SDL.h>
#include <utils.h>

#define ASTEROID_COUNT 5
#define ASTEROID_VARIANTS 3

typedef enum {
  ASTEROID_SIZE_SMALL,
  ASTEROID_SIZE_MEDIUM,
  ASTEROID_SIZE_BIG,
} asteroid_size;

extern SDL_Texture *asteroid_texture[ASTEROID_VARIANTS];
extern float asteroid_points[ASTEROID_VARIANTS];

typedef struct {
  bool alive;
  double angle;
  asteroid_size size;
  SDL_Texture *texture;
  SDL_Rect position;
  float point;
} asteroid_t;

void asteroid_init(SDL_Renderer *renderer);
SDL_Rect asteroid_generate_position();
asteroid_t asteroid_create();
void asteroid_render(asteroid_t *asteroid, SDL_Renderer *renderer);
void asteroid_update(asteroid_t *asteroid, float delta_time);
void asteroid_destroy();

#endif
