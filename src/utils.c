#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <utils.h>

SDL_Texture *load_texture(SDL_Renderer *renderer, const char *path) {
  SDL_Texture *texture = NULL;
  SDL_Surface *surface = IMG_Load(path);
  if (!surface) {
    fprintf(stderr, "error: cannot load image %s SDL_Image: %s\n", path,
            IMG_GetError());
  } else {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
      fprintf(stderr, "error: cannot create texture from %s SDL_Image: %s\n",
              path, SDL_GetError());
    }
    SDL_FreeSurface(surface);
  }
  return texture;
}

SDL_Texture *load_from_rendered_text(SDL_Renderer *renderer, TTF_Font *font,
                                     const char *string) {
  SDL_Texture *texture = NULL;
  SDL_Color color;
  color.r = 0xff;
  color.g = 0xff;
  color.b = 0xff;
  SDL_Surface *surface = TTF_RenderText_Solid(font, string, color);
  if (!surface) {
    fprintf(stderr, "error: cannot create surface from text SDL_ttf: %s\n",
            SDL_GetError());
  } else {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
      fprintf(stderr, "error: cannot create texture from SDL_Surface: %s\n",
              SDL_GetError());
    }
    SDL_FreeSurface(surface);
  }
  return texture;
}
