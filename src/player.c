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

void player_destroy(player_t *player) {
  if (player->texture) {
    SDL_DestroyTexture(player->texture);
  }
}