#pragma once

#include <algorithm>
#include <iostream>

struct step_t {
    step_t(int x, int y) :
            x{x},
            y{y} {}

    int x, y;
};

struct field_t {
    field_t() {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if ((row + col) % 2 == 0) {
                    fld[row][col] = '.';
                    continue;
                }
                if (row < 3) {
                    fld[row][col] = 'b';
                }
                if (row > 2 && row < 5) {
                    fld[row][col] = '0';
                }
                if (row > 4) {
                    fld[row][col] = 'w';
                }
            }
        }
    }

    char fld[8][8];
};
