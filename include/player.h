#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define PLAYER_SPRITE_PATH "assets/sprites/player.png"
#define PLAYER_VELOCITY 350
#define PLAYER_TURN_ANGLE 7.5
#define BULLET_SPRITE_PATH "assets/sprites/bullet.png"
#define BULLET_COUNT 3
#define BULLET_VELOCITY 500

enum player_directions { eUp, eDown, eLeft, eRight, eNumDirections };

typedef struct {
  SDL_Rect position;
  float angle;
  bool alive;
} bullet_t;

typedef struct {
  SDL_Texture *texture;
  SDL_Texture *bullet_texture;
  // props
  float angle;

  SDL_Rect position;
  bullet_t bullets[BULLET_COUNT];
  bool directions[eNumDirections];
} player_t;

player_t player_create(SDL_Renderer *renderer);
void player_render(player_t *player, SDL_Renderer *renderer);
void player_handle_event(player_t *player, SDL_Event *event);
void player_update(player_t *player, float delta_time);
void player_shoot_bullets(player_t *player);
void player_destroy(player_t *player);

#endif
