#include <memory>
#include "game/game.h"
#include "strategies/human.h"
#include "strategies/computer.h"


int main() {
  auto player1 = std::make_shared<computer_strategy_t>("First player");
  auto player2 = std::make_shared<computer_strategy_t>("Second player");

  for (int i = 0; i < 50; ++i) {
    game_t game(player1, player2);
    game.play();
  }

  player1->print_stat();
  player2->print_stat();
//    auto player1 = std::make_shared<human_strategy_t>("Player 1");
//    auto player2 = std::make_shared<human_strategy_t>("Player 2");
//
//    game_t game(player1, player2);
//    game.play();

    return 0;
}
