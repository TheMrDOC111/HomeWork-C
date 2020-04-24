#include "human.h"

#include <iostream>

void human_strategy_t::on_win() {
  std::cout << "You win!" << std::endl;
}
void human_strategy_t::on_lose() {
  std::cout << "You lose!" << std::endl;
}
void human_strategy_t::on_tie() {
  std::cout << "Tie!" << std::endl;
}

step_t human_strategy_t::make_step(const field_t &fld) {
  std::cout << "Field:" << std::endl;
  for (const auto &line : fld.fld) {
    for (char c : line) {
      std::cout << c;
    }
    std::cout << std::endl;
  }
  std::cout << "Type coordinates: " << std::endl;
  int x, y;
  std::cin >> x >> y;
  return {x, y};
}

void human_strategy_t::on_incorrect_step(const step_t &step) const {
  std::cout << "Incorrect step: x: " << step.x << "; y: " << step.y << std::endl;
}
