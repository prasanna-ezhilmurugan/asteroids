#include <game.h>

game_t game;

int main() {
  bool load_game_status = load_game(&game);
  if (!load_game_status) {
    fprintf(stderr, "error: cannot load game");
    return EXIT_FAILURE;
  }

  init_game(&game);
  while (game.state != QUIT) {
    handle_event(&game);
    render(&game);
    if (game.state == RUNNING)
      update(&game);
  }

  quit_game(&game);
  return 0;
}
