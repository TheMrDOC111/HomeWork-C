#include "computer.h"

#include <cassert>
#include <iostream>
#include <vector>


computer_strategy_t::computer_strategy_t(std::string name) :
  name(std::move(name)) {}

step_t computer_strategy_t::make_step(const field_t &fld) {
  std::vector<std::pair<int, int>> empty_coordinates;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (fld.fld[i][j] == '.') {
        empty_coordinates.emplace_back(i, j);
      }
    }
  }
  assert(!empty_coordinates.empty());
  std::random_shuffle(empty_coordinates.begin(), empty_coordinates.end());
  auto elem = empty_coordinates.back();
  return {elem.first + 1, elem.second + 1};
}

void computer_strategy_t::print_stat() const {
  std::cout << "Random model [" << name << "]: " << std::endl;
  computer_interface_t::print_stat();
}
