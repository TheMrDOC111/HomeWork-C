#include "computer.h"

#include <cassert>
#include <iostream>
#include <random>
#include <vector>


computer_strategy_t::computer_strategy_t(std::string name) :
        name(std::move(name)) {
    checkers = 12;
}

step_t computer_strategy_t::select_step(const field_t &field) {
    std::vector<step_t> checkers;

    if (player_num == 0) {
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (field.fld[r][c] == 'w') {
                    if ((field.fld[r - 1][c - 1] == 'b' || field.fld[r - 1][c - 1] == 'B') &&
                        (field.fld[r - 2][c - 2] == '0')) { // левый верхний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                    if ((field.fld[r - 1][c + 1] == 'b' || field.fld[r - 1][c + 1] == 'B') &&
                        (field.fld[r - 2][c + 2] == '0')) { // правый верхний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                    if ((field.fld[r + 1][c - 1] == 'b' || field.fld[r + 1][c - 1] == 'B') &&
                        (field.fld[r + 2][c - 2] == '0')) { // левый нижний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                    if ((field.fld[r + 1][c + 1] == 'b' || field.fld[r - 1][c + 1] == 'B') &&
                        (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                }
            }
        }

        if (checkers.empty()) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'w') {
                        if (field.fld[row - 1][col - 1] == '0' || field.fld[row - 1][col + 1] == '0') {
                            checkers.emplace_back(row + 1, col + 1);
                        }
                    }
                }
            }
        }
    }
    if (player_num == 1) {
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (field.fld[r][c] == 'b') {
                    if ((field.fld[r - 1][c - 1] == 'w' || field.fld[r - 1][c - 1] == 'W') &&
                        (field.fld[r - 2][c - 2] == '0')) { // левый верхний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                    if ((field.fld[r - 1][c + 1] == 'w' || field.fld[r - 1][c + 1] == 'W') &&
                        (field.fld[r - 2][c + 2] == '0')) { // правый верхний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                    if ((field.fld[r + 1][c - 1] == 'w' || field.fld[r + 1][c - 1] == 'W') &&
                        (field.fld[r + 2][c - 2] == '0')) { // левый нижний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                    if ((field.fld[r + 1][c + 1] == 'w' || field.fld[r - 1][c + 1] == 'W') &&
                        (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                }
            }
        }

        if (checkers.empty()) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'b') {
                        if (field.fld[row - 1][col - 1] == '0' || field.fld[row - 1][col + 1] == '0') {
                            checkers.emplace_back(row + 1, col + 1);
                        }
                    }
                }
            }
        }
    }

    std::shuffle(checkers.begin(), checkers.end(), std::mt19937(std::random_device()()));
    selected_checker = checkers[0];
    return selected_checker;
}

step_t computer_strategy_t::make_step(const field_t &fld) {
    std::vector<step_t> cells;
    if (player_num == 0) {
        std::cout << selected_checker.r << ' ' << selected_checker.c << std::endl;
        if (selected_checker.r - 1 && selected_checker.c + 1) {
            cells.emplace_back(selected_checker.r - 1, selected_checker.c + 1);
        }
        if (selected_checker.r - 1 && selected_checker.c - 1) {
            cells.emplace_back(selected_checker.r - 1, selected_checker.c - 1);
        }
    }
    std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));

    return cells.front();
}

step_t computer_strategy_t::attack_step(const field_t &field) {
    std::vector<step_t> cells;
    int r = selected_checker.r - 1;
    int c = selected_checker.c - 1;
    if (player_num == 0) {
        if (field.fld[r][c] == 'w') {
            if ((field.fld[r - 1][c - 1] == 'b' || field.fld[r - 1][c - 1] == 'B') &&
                (field.fld[r - 2][c - 2] == '0')) { // левый верхний
                cells.emplace_back(r - 2 + 1, c - 2 + 1);
            }
            if ((field.fld[r - 1][c + 1] == 'b' || field.fld[r - 1][c + 1] == 'B') &&
                (field.fld[r - 2][c + 2] == '0')) { // правый верхний
                cells.emplace_back(r - 2 + 1, c + 2 + 1);
            }
            if ((field.fld[r + 1][c - 1] == 'b' || field.fld[r + 1][c - 1] == 'B') &&
                (field.fld[r + 2][c - 2] == '0')) { // левый нижний
                cells.emplace_back(r + 2 + 1, c - 2 + 1);
            }
            if ((field.fld[r + 1][c + 1] == 'b' || field.fld[r - 1][c + 1] == 'B') &&
                (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                cells.emplace_back(r + 2 + 1, c + 2 + 1);
            }
        }
    }
    std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));
    return cells.front();
}

void computer_strategy_t::print_stat() const {
    std::cout << "Random model [" << name << "]: " << std::endl;
    computer_interface_t::print_stat();
}




