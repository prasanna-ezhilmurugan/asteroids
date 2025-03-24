#include <asteroids.h>

void asteroid_init(SDL_Renderer *renderer) {
  asteroid_texture[ASTEROID_SIZE_BIG] =
      load_texture(renderer, "assets/sprites/asteroid_big.png");
  asteroid_texture[ASTEROID_SIZE_MEDIUM] =
      load_texture(renderer, "assets/sprites/asteroid_medium.png");
  asteroid_texture[ASTEROID_SIZE_SMALL] =
      load_texture(renderer, "assets/sprites/asteroid_small.png");
}

asteroid_t asteroid_create() {
  asteroid_t asteroid;

  asteroid.size = ASTEROID_SIZE_SMALL;
  asteroid.angle = 0.0;
  asteroid.texture = asteroid_texture[asteroid.size];
  asteroid.position = get_rect(asteroid.texture);
  asteroid.position.x = 0;
  asteroid.position.y = 0;

  return asteroid;
}

void asteroid_render(asteroid_t *asteroid, SDL_Renderer *renderer) {
  SDL_RenderCopyEx(renderer, asteroid->texture, NULL, &asteroid->position,
                   asteroid->angle, NULL, SDL_FLIP_NONE);
}

void asteroid_update(asteroid_t *asteroid, float delta_time) {
  asteroid->position.x += 100.0f * delta_time;
  asteroid->position.y += 100.0f * delta_time;
  asteroid->angle += 15 * delta_time;
}

void asteroid_destroy() {
  for (size_t i = 0; i < ASTEROID_TEXTURES; i++) {
    if (asteroid_texture[0]) {
      SDL_DestroyTexture(asteroid_texture[i]);
      asteroid_texture[i] = NULL;
    }
  }
}
