#include <game.h>

game_t game;

int main() {
  game.state[RUNNING] = initialize_game(&game);
  while (game.state[RUNNING]) {
    handle_event(&game);
    render(&game);
    update(&game);
  }
  quit_game(&game);
  return 0;
}
