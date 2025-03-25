#include <asteroids.h>
#include <stdlib.h>
#include <time.h>

SDL_Texture *asteroid_texture[ASTEROID_VARIANTS] = {0};
float asteroid_point[ASTEROID_VARIANTS] = {1, 2, 3};

void asteroid_init(SDL_Renderer *renderer) {
  asteroid_texture[ASTEROID_SIZE_BIG] =
      load_texture(renderer, "assets/sprites/asteroid_big.png");
  asteroid_texture[ASTEROID_SIZE_MEDIUM] =
      load_texture(renderer, "assets/sprites/asteroid_medium.png");
  asteroid_texture[ASTEROID_SIZE_SMALL] =
      load_texture(renderer, "assets/sprites/asteroid_small.png");
  srand(time(NULL));
}

asteroid_t asteroid_create() {
  asteroid_t asteroid;

  asteroid.alive = true;
  asteroid.angle = 0.0;
  asteroid.size = rand() % ASTEROID_VARIANTS;

  asteroid.texture = asteroid_texture[asteroid.size];
  asteroid.position = get_rect(asteroid.texture);

  asteroid.point = asteroid_point[asteroid.size];

  if (rand() % 2 == 0) {
    asteroid.position.x = 0;
    asteroid.position.y = rand() % WINDOW_HEIGHT;
  } else {
    asteroid.position.x = rand() % WINDOW_WIDTH;
    asteroid.position.y = 0;
  }

  return asteroid;
}

void asteroid_render(asteroid_t *asteroid, SDL_Renderer *renderer) {
  SDL_RenderCopyEx(renderer, asteroid->texture, NULL, &asteroid->position,
                   asteroid->angle, NULL, SDL_FLIP_NONE);
}

void asteroid_update(asteroid_t *asteroid, float delta_time) {
  asteroid->position.x += 100.0f * delta_time;
  asteroid->position.y += 100.0f * delta_time;
  if (asteroid->position.x < 0 || asteroid->position.x > WINDOW_WIDTH) {
    asteroid->alive = false;
  }
  if (asteroid->position.y < 0 || asteroid->position.y > WINDOW_HEIGHT) {
    asteroid->alive = false;
  }
  asteroid->angle += 15 * delta_time;
}

void asteroid_destroy() {
  for (size_t i = 0; i < ASTEROID_VARIANTS; i++) {
    if (asteroid_texture[0]) {
      SDL_DestroyTexture(asteroid_texture[i]);
      asteroid_texture[i] = NULL;
    }
  }
}
