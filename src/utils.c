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
SDL_Rect get_rect(SDL_Texture *texture) {
  SDL_Rect position = {0};
  int texture_width = 0, texture_height = 0;
  SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);
  position = (SDL_Rect){.x = (WINDOW_WIDTH - texture_width) / 2,
                        .y = (WINDOW_HEIGHT - texture_height) / 2,
                        texture_width,
                        texture_height};
  return position;
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

bool detect_collision(SDL_Rect A, SDL_Rect B) {

  int left_A = A.x;
  int right_A = A.x + A.w;
  int top_A = A.y;
  int bottom_A = A.y + A.h;

  int left_B = B.x;
  int right_B = B.x + B.w;
  int top_B = B.y;
  int bottom_B = B.y + B.h;

  if (bottom_A < top_B) {
    return false;
  }
  if (top_A >= bottom_B) {
    return false;
  }
  if (right_A <= left_B) {
    return false;
  }
  if (left_A >= right_B) {
    return false;
  }

  return true;
}
