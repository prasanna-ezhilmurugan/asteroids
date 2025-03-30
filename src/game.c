#include <SDL2/SDL_image.h>
#include <game.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <utils.h>

bool load_game(game_t *game) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "error: cannot initialize SDL: %s\n", SDL_GetError());
    return false;
  }
  /* Initialize SDL_Image */
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    fprintf(stderr, "error: cannot initialize SDL image: %s\n", IMG_GetError());
    return false;
  }
  /* Initialize TTF_Font */
  if (TTF_Init() != 0) {
    fprintf(stderr, "error: cannot initialize SDL font: %s", TTF_GetError());
    return false;
  }

  /* Create window or throw */
  game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (!game->window) {
    fprintf(stderr, "error: cannot create SDL window: %s\n", SDL_GetError());
    return false;
  }

  /* Create renderer or throw */
  game->renderer = SDL_CreateRenderer(
      game->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!game->renderer) {
    fprintf(stderr, "error: cannot create SDL renderer: %s\n", SDL_GetError());
    return false;
  }

  /* Create font or throw */
  game->font =
      TTF_OpenFont("assets/fonts/JetBrainsMonoNLNerdFont-Bold.ttf", 48);
  if (!game->font) {
    fprintf(stderr, "error: cannot create SDL font: %s", TTF_GetError());
    return false;
  }

  game->start_screen_texture =
      load_from_rendered_text(game->renderer, game->font, "START GAME");
  game->start_screen_rect = get_rect(game->start_screen_texture);

  game->over_screen_texture =
      load_from_rendered_text(game->renderer, game->font, "GAME OVER");
  game->over_screen_rect = get_rect(game->over_screen_texture);

  /* Score board position */
  game->score_rect.x = WINDOW_WIDTH - game->score_rect.w;
  game->score_rect.y = 0;

  game->life = 1;
  return true;
}

void init_game(game_t *game) {
  game->tick_count = 0;
  game->score = 0;
  sprintf(game->score_string, "SCORE: %d ", game->score);

  game->player = player_create(game->renderer);
  asteroid_init(game->renderer);

  game->score_texture =
      load_from_rendered_text(game->renderer, game->font, game->score_string);
  game->score_rect = get_rect(game->score_texture);
  game->score_rect.x = WINDOW_WIDTH - game->score_rect.w;
  game->score_rect.y = 0;
}

void handle_event(game_t *game) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      game->state = QUIT;
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (game->state == START) {
        game->state = RUNNING;
      }
      break;
    default:
      player_handle_event(&game->player, &event);
    }
  }
}

void render(game_t *game) {
  SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
  SDL_RenderClear(game->renderer);

  if (game->state == START) {
    SDL_RenderCopy(game->renderer, game->start_screen_texture, NULL,
                   &game->start_screen_rect);
  } else if (game->state == RUNNING) {
    player_render(&game->player, game->renderer);
    for (size_t i = 0; i < ASTEROID_COUNT; i++) {
      if (game->asteroids[i].alive) {
        asteroid_render(&game->asteroids[i], game->renderer);
      }
    }
    SDL_RenderCopy(game->renderer, game->score_texture, NULL,
                   &game->score_rect);
  } else if (game->state == OVER) {
    SDL_RenderCopy(game->renderer, game->over_screen_texture, NULL,
                   &game->over_screen_rect);
  }

  SDL_RenderPresent(game->renderer);
}

void update(game_t *game) {
  /* Wait until 16ms has elapsed since last frame */
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), game->tick_count + 16))
    ;
  /* Delta time is the difference in ticks from the last frame (seconds) */
  float delta_time = (SDL_GetTicks() - game->tick_count) / 1000.0f;
  game->tick_count = SDL_GetTicks();
  /* Clamp maximum delta time value */
  if (delta_time > 0.05f) {
    delta_time = 0.05f;
  }

  player_update(&game->player, delta_time);

  for (size_t i = 0; i < ASTEROID_COUNT; i++) {
    asteroid_update(&game->asteroids[i], delta_time);
    if (detect_collision(game->player.position, game->asteroids[i].position,
                         (game->asteroids[i].size + 1) * ASTEROID_PADDING)) {
      if (game->life == 0) {
        game->state = OVER;
      } else {
        game->life--;
        // go back to initial state
      }
    }
    if (!game->asteroids[i].alive) {
      game->asteroids[i] = asteroid_create();
    }
    for (size_t j = 0; j < BULLET_COUNT; j++) {
      if (detect_collision(game->player.bullets[i].position,
                           game->asteroids[i].position, 0)) {
        game->asteroids[i].point--;
      }
      if (game->asteroids[i].point == 0) {
        game->asteroids[i].alive = false;
      }
    }
  }

  /* Score update */
  game->score++;
  sprintf(game->score_string, "SCORE: %d ", game->score);
  game->score_texture =
      load_from_rendered_text(game->renderer, game->font, game->score_string);
}

void quit_game(game_t *game) {
  if (game->window) {
    SDL_DestroyWindow(game->window);
    game->window = NULL;
  }
  if (game->renderer) {
    SDL_DestroyRenderer(game->renderer);
    game->renderer = NULL;
  }
  if (game->start_screen_texture) {
    SDL_DestroyTexture(game->start_screen_texture);
    game->start_screen_texture = NULL;
  }
  if (game->over_screen_texture) {
    SDL_DestroyTexture(game->over_screen_texture);
    game->over_screen_texture = NULL;
  }
  if (game->score_texture) {
    SDL_DestroyTexture(game->score_texture);
    game->score_texture = NULL;
  }
  player_destroy(&game->player);
  asteroid_destroy();
  SDL_Quit();
}
