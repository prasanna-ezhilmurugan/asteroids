#include <game.h>

game_t game;

int main() {
  game.state = initialize_game(&game);
  while (game.state != QUIT) {
    handle_event(&game);
    render(&game);
    update(&game);
  }
  quit_game(&game);
  return 0;
}
