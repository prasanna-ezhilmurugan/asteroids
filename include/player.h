#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define PLAYER_IDLE_SPRITE_PATH "assets/sprites/player_idle.png"
#define PLAYER_THRUSTING_SPRITE_PATH "assets/sprites/player_thrusting.png"
#define PLAYER_MAX_VELOCITY 400
#define PLAYER_ACCELERATION 300
#define PLAYER_TURN_ANGLE 7.5
#define BULLET_SPRITE_PATH "assets/sprites/bullet.png"
#define BULLET_COUNT 5
#define BULLET_VELOCITY 500

enum player_directions { eUp, eDown, eLeft, eRight, eNumDirections };

typedef struct {
  SDL_Rect position;
  float angle;
  bool alive;
} bullet_t;

typedef struct {
  SDL_Texture *texture_idle;
  SDL_Texture *texture_thrusting;
  SDL_Texture *bullet_texture;
  // props
  float angle;
  float velocity;

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
