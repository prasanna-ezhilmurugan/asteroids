#include <SDL2/SDL_events.h>
#include <math.h>
#include <player.h>
#include <stdio.h>
#include <utils.h>

player_t player_create(SDL_Renderer *renderer) {
  player_t player = {};
  player.texture_idle = load_texture(renderer, PLAYER_IDLE_SPRITE_PATH);
  player.texture_thrusting =
      load_texture(renderer, PLAYER_THRUSTING_SPRITE_PATH);
  player.position = get_rect(player.texture_idle);
  player.bullet_texture = load_texture(renderer, BULLET_SPRITE_PATH);

  player.angle = 0;
  for (size_t i = 0; i < BULLET_COUNT; i++) {
    player.bullets[i].alive = false;
  }

  return player;
}

void player_render(player_t *player, SDL_Renderer *renderer) {
  if (player->directions[eUp]) {
    SDL_RenderCopyEx(renderer, player->texture_thrusting, NULL,
                     &player->position, player->angle, NULL, SDL_FLIP_NONE);
  } else {
    SDL_RenderCopyEx(renderer, player->texture_idle, NULL, &player->position,
                     player->angle, NULL, SDL_FLIP_NONE);
  }
  for (size_t i = 0; i < BULLET_COUNT; i++) {
    if (player->bullets[i].alive) {
      SDL_RenderCopy(renderer, player->bullet_texture, NULL,
                     &player->bullets[i].position);
    }
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
  /* Updating position and adding thrusting force */
  player->position.x += player->velocity * cos(RAD(player->angle)) * delta_time;
  player->position.y += player->velocity * sin(RAD(player->angle)) * delta_time;
  if (player->directions[eUp]) {
    player->velocity += PLAYER_ACCELERATION * delta_time;
  } else {
    if (player->velocity > 0) {
      player->velocity -= PLAYER_ACCELERATION * delta_time;
    }
  }
  if (player->directions[eLeft]) {
    player->angle -= PLAYER_TURN_ANGLE;
  }
  if (player->directions[eRight]) {
    player->angle += PLAYER_TURN_ANGLE;
  }

  // bounding the player
  if (player->position.x > WINDOW_WIDTH - player->position.w) {
    player->position.x = 0;
  }
  if (player->position.x < 0) {
    player->position.x = WINDOW_WIDTH - player->position.w;
  }
  if (player->position.y > WINDOW_HEIGHT - player->position.h) {
    player->position.y = 0;
  }
  if (player->position.y < 0) {
    player->position.y = WINDOW_HEIGHT - player->position.h;
  }

  // bullet update and bounding the bullet
  for (size_t i = 0; i < BULLET_COUNT; i++) {
    if (player->bullets[i].alive) {
      player->bullets[i].position.x +=
          BULLET_VELOCITY * cos(RAD(player->bullets[i].angle)) * delta_time;
      player->bullets[i].position.y +=
          BULLET_VELOCITY * sin(RAD(player->bullets[i].angle)) * delta_time;
      if (player->bullets[i].position.x < 0 ||
          player->bullets[i].position.x >= WINDOW_WIDTH) {
        player->bullets[i].alive = false;
      }
      if (player->bullets[i].position.y < 0 ||
          player->bullets[i].position.y >= WINDOW_HEIGHT) {
        player->bullets[i].alive = false;
      }
    }
  }
}

void player_shoot_bullets(player_t *player) {
  for (size_t i = 0; i < BULLET_COUNT; i++) {
    if (!player->bullets[i].alive) {
      player->bullets[i].alive = true;
      player->bullets[i].angle = player->angle;
      player->bullets[i].position = get_rect(player->bullet_texture);
      player->bullets[i].position.x =
          player->position.x + player->position.w / 3;
      player->bullets[i].position.y =
          player->position.y + player->position.h / 3;
      break;
    }
  }
}
void player_destroy(player_t *player) {
  if (player->texture_idle) {
    SDL_DestroyTexture(player->texture_idle);
  }
  if (player->texture_thrusting) {
    SDL_DestroyTexture(player->texture_thrusting);
  }
  if (player->bullet_texture) {
    SDL_DestroyTexture(player->bullet_texture);
  }
}
