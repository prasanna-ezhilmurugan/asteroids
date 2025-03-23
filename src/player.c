#include <SDL_events.h>
#include <math.h>
#include <player.h>
#include <stdio.h>
#include <utils.h>

player_t player_create(SDL_Renderer *renderer, const char *path) {
  player_t player = {};
  player.texture = load_texture(renderer, path);
  if (!player.texture) {
    fprintf(stderr, "error: cannot create player texture\n");
    exit(EXIT_FAILURE);
  }

  // player.dx = 0;
  // player.dy = 0;

  // position and size of the texture
  int texture_width = 0, texture_height = 0;
  SDL_QueryTexture(player.texture, NULL, NULL, &texture_width, &texture_height);
  player.position = (SDL_Rect){.x = (WINDOW_WIDTH - texture_width) / 2,
                               .y = (WINDOW_HEIGHT - texture_height) / 2,
                               texture_width,
                               texture_height};

  player.angle = 0;

  return player;
}

void player_render(player_t *player, SDL_Renderer *renderer) {
  SDL_RenderCopyEx(renderer, player->texture, NULL, &player->position,
                   player->angle, NULL, SDL_FLIP_NONE);
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
}

void player_destroy(player_t *player) {
  if (player->texture) {
    SDL_DestroyTexture(player->texture);
  }
}
