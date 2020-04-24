#pragma once

#include <algorithm>

struct step_t {
  step_t(int x, int y) :
    x{x},
    y{y} {}
  int x, y;
};

struct field_t {
  field_t() {
    for (char *line : fld) {
      std::fill(line, line + 3, '.');
    }
  }

  char fld[3][3];
};
