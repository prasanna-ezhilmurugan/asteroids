#include <SDL_events.h>
#include <math.h>
#include <player.h>
#include <stdio.h>
#include <utils.h>

player_t player_create(SDL_Renderer *renderer) {
  player_t player = {};
  player.texture = load_texture(renderer, PLAYER_SPRITE_PATH);
  player.position = get_rect(player.texture);
  /* if (!player.texture) { */
  /*   fprintf(stderr, "error: cannot create player texture\n"); */
  /*   exit(EXIT_FAILURE); */
  /* } */
  player.bullet_texture = load_texture(renderer, BULLET_SPRITE_PATH);

  player.angle = 0;

  return player;
}

void player_render(player_t *player, SDL_Renderer *renderer) {
  SDL_RenderCopyEx(renderer, player->texture, NULL, &player->position,
                   player->angle, NULL, SDL_FLIP_NONE);
  if (player->bullet.alive) {
    SDL_RenderCopy(renderer, player->bullet_texture, NULL,
                   &player->bullet.position);
  }
}

void player_handle_event(player_t *player, SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      player->directions[eUp] = true;
      break;
    case SDLK_DOWN:
      break;
    case SDLK_RIGHT:
      player->directions[eRight] = true;
      break;
    case SDLK_LEFT:
      player->directions[eLeft] = true;
      break;
    case SDLK_SPACE:
      player_shoot_bullets(player);
      break;
    }
  }

  if (event->type == SDL_KEYUP) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      player->directions[eUp] = false;
      break;
    case SDLK_LEFT:
      player->directions[eLeft] = false;
      break;
    case SDLK_RIGHT:
      player->directions[eRight] = false;
      break;
    }
  }
}

void player_update(player_t *player, float delta_time) {
  if (player->directions[eUp]) {
    player->position.x += 350 * cos(RAD(player->angle)) * delta_time;
    player->position.y += 350 * sin(RAD(player->angle)) * delta_time;
  }
  if (player->directions[eLeft]) {
    player->angle -= 7.50;
  }
  if (player->directions[eRight]) {
    player->angle += 7.50;
  }
  if (player->bullet.alive) {
    player->bullet.position.x +=
        BULLET_VELOCITY * cos(RAD(player->bullet.angle));
    player->bullet.position.y +=
        BULLET_VELOCITY * sin(RAD(player->bullet.angle));
  }
}

void player_shoot_bullets(player_t *player) {
  player->bullet.alive = true;
  player->bullet.angle = player->angle;
  player->bullet.position = get_rect(player->bullet_texture);
  player->bullet.position.x = player->position.x;
  player->bullet.position.y = player->position.y;
}
void player_destroy(player_t *player) {
  if (player->texture) {
    SDL_DestroyTexture(player->texture);
  }
}
