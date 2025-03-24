#include <asteroids.h>

asteroid_t asteroid_create(SDL_Renderer *renderer) {
  asteroid_t asteroid;

  asteroid.size = ASTEROID_SIZE_BIG;
  asteroid.angle = 0.0;
  asteroid.texture = load_texture(renderer, "assets/sprites/big.png");
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
