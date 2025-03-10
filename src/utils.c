#include <SDL2/SDL_image.h>

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
