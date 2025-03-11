#include <SDL_events.h>
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

  player.dx = 0;
  player.dy = 0;

  // position and size of the texture
  int texture_width = 0, texture_height = 0;
  SDL_QueryTexture(player.texture, NULL, NULL, &texture_width, &texture_height);
  player.position = (SDL_Rect){.x = (WINDOW_WIDTH - texture_width) / 2,
                               .y = (WINDOW_HEIGHT - texture_height) / 2,
                               texture_width,
                               texture_height};

  return player;
}

void player_render(player_t *player, SDL_Renderer *renderer) {
  SDL_RenderCopyEx(renderer, player->texture, NULL, &player->position, 0, NULL,
                   SDL_FLIP_NONE);
}

void player_handle_event(player_t *player, SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    switch (event->key.keysym.sym) {
    case SDLK_UP:
      player->dy += 2;
      break;
    case SDLK_DOWN:
      player->dy -= 2;
      break;
    case SDLK_RIGHT:
      player->dx += 2;
      break;
    case SDLK_LEFT:
      player->dx -= 2;
      break;
    }
  }
}

void player_update(player_t *player) {
  player->position.x += player->dx;
  if (player->position.x < 0 ||
      player->position.x + player->position.w > WINDOW_WIDTH) {
    player->position.x = 0;
  }

  player->position.y += player->dy;
  if (player->position.y < 0 ||
      player->position.y + player->position.h > WINDOW_HEIGHT) {
    player->position.y = 0;
  }
}

void player_destroy(player_t *player) {
  if (player->texture) {
    SDL_DestroyTexture(player->texture);
  }
}