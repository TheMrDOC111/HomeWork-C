#include "computer2.h"
#include <string>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>


computer_strategy_second_t::computer_strategy_second_t(std::string name):
        name(std::move(name)) {
}

step_t computer_strategy_second_t::select_step(const field_t &field) {
    std::vector<step_t> checkers;
    if (player_num == 0) {
        for (int r = 0; r < 8; ++r) {
            for (int c = 0; c < 8; ++c) {
                if (field.fld[r][c] == 'W') {
                    int change_step[2] = {-1, 1};
                    for (auto &i: change_step) {
                        for (auto &j: change_step) {
                            int k = 0;
                            while (k < 8) {
                                ++k;
                                if ((field.fld[r + i * k][c + j * k] == 'b' ||
                                     field.fld[r + i * k][c + j * k] == 'B') &&
                                    field.fld[r + i * (k + 1)][c + j * (k + 1)] == '0') {
                                    checkers.emplace_back(r + 1, c + 1);
                                    break;
                                }
                                if (field.fld[r + i * k][c + j * k] != '0') {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }


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
                    if ((field.fld[r + 1][c + 1] == 'b' || field.fld[r + 1][c + 1] == 'B') &&
                        (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                }
            }
        }

        if (checkers.empty()) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'W') {
                        if (field.fld[row - 1][col - 1] == '0' || field.fld[row - 1][col + 1] == '0' ||
                            field.fld[row + 1][col - 1] == '0' || field.fld[row + 1][col + 1] == '0') {
                            checkers.emplace_back(row + 1, col + 1);
                        }
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
                if (field.fld[r][c] == 'B') {
                    int change_step[2] = {-1, 1};
                    for (auto &i: change_step) {
                        for (auto &j: change_step) {
                            int k = 0;
                            while (k < 8) {
                                ++k;
                                if ((field.fld[r + i * k][c + j * k] == 'w' ||
                                     field.fld[r + i * k][c + j * k] == 'W') &&
                                    field.fld[r + i * (k + 1)][c + j * (k + 1)] == '0') {
                                    checkers.emplace_back(r + 1, c + 1);
                                    break;
                                }
                                if (field.fld[r + i * k][c + j * k] != '0') {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

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
                    if ((field.fld[r + 1][c + 1] == 'w' || field.fld[r + 1][c + 1] == 'W') &&
                        (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                        checkers.emplace_back(r + 1, c + 1);
                    }
                }
            }
        }


        if (checkers.empty()) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'B') {
                        if (field.fld[row - 1][col - 1] == '0' || field.fld[row - 1][col + 1] == '0' ||
                            field.fld[row + 1][col - 1] == '0' || field.fld[row + 1][col + 1] == '0') {
                            checkers.emplace_back(row + 1, col + 1);
                        }
                    }
                }
            }
        }

        if (checkers.empty()) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'b') {
                        if (field.fld[row + 1][col - 1] == '0' || field.fld[row + 1][col + 1] == '0') {
                            checkers.emplace_back(row + 1, col + 1);
                        }
                    }
                }
            }
        }
    }

//    std::shuffle(checkers.begin(), checkers.end(), std::mt19937(std::random_device()()));
//    std:: cout << "select_step "<< checkers.size() << std::endl;
//    std:: cout << "player "<< name << std::endl;
    selected_checker = checkers[0];

    return selected_checker;
}

step_t computer_strategy_second_t::make_step(const field_t &fld) {
    std::vector<step_t> cells;
    char cell = fld.fld[selected_checker.r - 1][selected_checker.c - 1];
    if (player_num == 0) {
        if (cell == 'w') {
            if (fld.fld[selected_checker.r - 1 - 1][selected_checker.c + 1 - 1] == '0') {
                cells.emplace_back(selected_checker.r - 1 - 1 + 1, selected_checker.c + 1 - 1 + 1);
            }
            if (fld.fld[selected_checker.r - 1 - 1][selected_checker.c - 1 - 1] == '0') {
                cells.emplace_back(selected_checker.r - 1 - 1 + 1, selected_checker.c - 1 - 1 + 1);

            }
        }
        if (cell == 'W') {
            int change_step[2] = {-1, 1};
            for (auto &i: change_step) {
                for (auto &j: change_step) {
                    int k = 0;
                    while (true) {
                        ++k;
                        if (fld.fld[selected_checker.r - 1 + i * k][selected_checker.c - 1 + j * k] == '0') {
                            cells.emplace_back(selected_checker.r + i * k, selected_checker.c + j * k);
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
    if (player_num == 1) {
        if (cell == 'b') {
            if (fld.fld[selected_checker.r + 1 - 1][selected_checker.c + 1 - 1] == '0') {
                cells.emplace_back(selected_checker.r + 1 - 1 + 1, selected_checker.c + 1 - 1 + 1);
            }
            if (fld.fld[selected_checker.r + 1 - 1][selected_checker.c - 1 - 1] == '0') {
                cells.emplace_back(selected_checker.r + 1 - 1 + 1, selected_checker.c - 1 - 1 + 1);
            }
        }
        if (cell == 'B') {
            int change_step[2] = {-1, 1};
            for (auto &i: change_step) {
                for (auto &j: change_step) {
                    int k = 0;
                    while (true) {
                        ++k;
                        if (fld.fld[selected_checker.r - 1 + i * k][selected_checker.c - 1 + j * k] == '0') {
                            cells.emplace_back(selected_checker.r + i * k, selected_checker.c + j * k);
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
//    std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));
//    std:: cout << "make_step "<< cells.size() << std::endl;

    return cells.front();
}

step_t computer_strategy_second_t::attack_step(const field_t &field) {
    std::vector<step_t> cells;
    int r = selected_checker.r - 1;
    int c = selected_checker.c - 1;

    if (player_num == 0) {

        if (field.fld[r][c] == 'W') {
            int change_step[2] = {-1, 1};
            for (auto &i: change_step) {
                for (auto &j: change_step) {
                    int k = 0;
                    bool found = false;
                    while (k < 8) {
                        ++k;

                        if (field.fld[r + i * k][c + j * k] == 'W' || field.fld[r + i * k][c + j * k] == 'w') {
                            break;
                        }

                        if (found && field.fld[r + i * k][c + j * k] != '0') {
                            break;
                        }
                        if (found) {
                            cells.emplace_back(r + i * k + 1, c + j * k + 1);
                        }
                        if ((field.fld[r + i * k][c + j * k] == 'b' ||
                             field.fld[r + i * k][c + j * k] == 'B')) {
                            found = true;
                        }

                    }
                }

            }
        }

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
            if ((field.fld[r + 1][c + 1] == 'b' || field.fld[r + 1][c + 1] == 'B') &&
                (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                cells.emplace_back(r + 2 + 1, c + 2 + 1);
            }
        }
    }
    if (player_num == 1) {

        if (field.fld[r][c] == 'B') {
            int change_step[2] = {-1, 1};
            for (auto &i: change_step) {
                for (auto &j: change_step) {
                    int k = 0;
                    bool found = false;
                    while (k < 8) {
                        ++k;

                        if (field.fld[r + i * k][c + j * k] == 'B' || field.fld[r + i * k][c + j * k] == 'b') {
                            break;
                        }
                        if (found && field.fld[r + i * k][c + j * k] != '0') {
                            break;
                        }
                        if (found) {
                            cells.emplace_back(r + i * k + 1, c + j * k + 1);
                        }
                        if ((field.fld[r + i * k][c + j * k] == 'w' ||
                             field.fld[r + i * k][c + j * k] == 'W')) {
                            found = true;
                        }

                    }
                }

            }
        }

        if (field.fld[r][c] == 'b') {
            if ((field.fld[r - 1][c - 1] == 'w' || field.fld[r - 1][c - 1] == 'W') &&
                (field.fld[r - 2][c - 2] == '0')) { // левый верхний
                cells.emplace_back(r - 2 + 1, c - 2 + 1);
            }
            if ((field.fld[r - 1][c + 1] == 'w' || field.fld[r - 1][c + 1] == 'W') &&
                (field.fld[r - 2][c + 2] == '0')) { // правый верхний
                cells.emplace_back(r - 2 + 1, c + 2 + 1);
            }
            if ((field.fld[r + 1][c - 1] == 'w' || field.fld[r + 1][c - 1] == 'W') &&
                (field.fld[r + 2][c - 2] == '0')) { // левый нижний
                cells.emplace_back(r + 2 + 1, c - 2 + 1);
            }
            if ((field.fld[r + 1][c + 1] == 'w' || field.fld[r + 1][c + 1] == 'W') &&
                (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                cells.emplace_back(r + 2 + 1, c + 2 + 1);
            }
        }
    }

//    std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));
    //std:: cout << "attack_step " << cells.size() << std::endl;
    selected_checker = cells.front();
    return selected_checker;
}

void computer_strategy_second_t::print_stat() const {
    std::cout << "No random model [" << name << "]: " << std::endl;
    computer_interface_t::print_stat();
}




