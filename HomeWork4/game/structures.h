#pragma once

#include <algorithm>
#include <iostream>

struct step_t {
    step_t(int r, int c) :
            r{r},
            c{c} {}

    step_t() {}

    int r, c;
};

struct field_t {
    field_t() {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if ((row + col) % 2 == 0) {
                    fld[row][col] = '.';
                    continue;
                }else{
                    fld[row][col] = '0';
                }
                if (row < 3) {
                    fld[row][col] = 'b';
                } else if (row > 4) {
                    fld[row][col] = 'w';
                } else {
                    fld[row][col] = '0';
                }
            }
        }


    }

    char fld[8][8];
};
