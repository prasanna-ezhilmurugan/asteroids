#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#define RAD(angle) ((angle) * M_PI / 180.0)

#define WINDOW_TITLE "asteroids"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *path);
SDL_Rect get_rect(SDL_Texture *texture);
SDL_Texture *load_from_rendered_text(SDL_Renderer *renderer, TTF_Font *font,
                                     const char *string);
bool detect_collision(SDL_Rect A, SDL_Rect B, int padding);
#endif
