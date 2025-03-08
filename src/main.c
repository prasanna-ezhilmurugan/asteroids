#include <game.h>

game_t game;

int main() {
  game.is_running = initialize_game(&game);
  while (game.is_running) {
    handle_event(&game);
    render(&game);
  }
  quit_game(&game);
  return 0;
}
