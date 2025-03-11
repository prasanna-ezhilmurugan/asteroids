#ifndef UTILS_H
#define UTILS_H

#include <SDL2/SDL.h>

#define WINDOW_TITLE "asteroids"
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *path);
#endif