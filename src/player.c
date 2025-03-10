#include <SDL_render.h>
#include <player.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

player_t player_create(SDL_Renderer *renderer, const char *path) {
  player_t player = {};
  player.texture = load_texture(renderer, path);
  if (!player.texture) {
    fprintf(stderr, "error: cannot create player texture\n");
    exit(EXIT_FAILURE);
  }
  return player;
}

void player_render(player_t *player, SDL_Renderer *renderer) {
  SDL_RenderCopyEx(renderer, player->texture, NULL, NULL, 0, NULL,
                   SDL_FLIP_NONE);
}

void player_destroy(player_t *player) {
  if (player->texture) {
    SDL_DestroyTexture(player->texture);
  }
}