#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) :
  field() {
  players.push_back(first);
  players.push_back(second);
}

bool game_t::apply_step(const step_t &step, size_t player_num) {
  char &cell = field.fld[step.x - 1][step.y - 1];
  if (cell != '.') {
    return false;
  }

  if (player_num == 0) {
    cell = '#';
  } else {
    cell = '0';
  }
  return true;
}

bool game_t::is_win_line(int x, int y, int dx, int dy) const {
  char c = field.fld[x][y];
  if (c == '.') {
    return false;
  }
  for (int i = 0; i < 3; ++i) {
    if (c != field.fld[x + i * dx][y + i * dy]) {
      return false;
    }
  }
  return true;
}

game_t::game_outcome_t game_t::is_win() const {
  for (int i = 0; i < 3; ++i) {
    if (is_win_line(0, i, 1, 0) || is_win_line(i, 0, 0, 1)) {
      return WIN;
    }
  }
  if (is_win_line(0, 0, 1, 1) || is_win_line(0, 2, 1, -1)) {
    return WIN;
  }
  for (auto line : field.fld) {
    for (int j = 0; j < 3; ++j) {
      if (line[j] == '.') {
        return IN_PROGRESS;
      }
    }
  }
  return TIE;
}

void game_t::play() {
  size_t counter = 1;
  while (is_win() == IN_PROGRESS) {
    counter = (counter + 1) % 2;
    bool is_correct = false;
    while (!is_correct) {
      step_t step = players[counter]->make_step(field);
      is_correct = apply_step(step, counter);
      if (!is_correct) {
        players[counter]->on_incorrect_step(step);
      }
    }
  }

  if (is_win() == TIE) {
    for (const auto &p : players) {
      p->on_tie();
    }
    return;
  }

  for (size_t i = 0; i < players.size(); ++i) {
    if (i == counter) {
      players[i]->on_win();
    } else {
      players[i]->on_lose();
    }
  }
}
