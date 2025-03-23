#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define RAD(angle) ((angle) * M_PI / 180.0)

#define WINDOW_TITLE "asteroids"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *path);
SDL_Texture *load_from_rendered_text(SDL_Renderer *renderer, TTF_Font *font,
                                     const char *string);
#endif
