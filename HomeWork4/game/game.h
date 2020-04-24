#pragma once

#include <memory>
#include <vector>

#include "../strategies/interface.h"
#include "structures.h"

class game_t {
public:
  using player_t = std::shared_ptr<strategy_interface_t>;
  game_t(const player_t &first, const player_t &second);

  void play();

private:
  enum game_outcome_t {
    WIN,
    TIE,
    IN_PROGRESS
  };

  bool is_win_line(int x, int y, int dx, int dy) const;
  game_outcome_t is_win() const;
  bool apply_step(const step_t &step, size_t player_num);

  field_t field;
  std::vector<player_t> players;
};

