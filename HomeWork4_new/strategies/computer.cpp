#include "computer.h"

#include <iostream>
#include <vector>
#include <random>

computer_strategy_t::computer_strategy_t(std::string name) :
        name(std::move(name)) {}

step_t computer_strategy_t::select_step(const field_t &field) {
    std::vector<std::pair<int, int>> checkers;
    check_all_checkers(checkers, player_num, field);
    if (!checkers.empty()) {
        std::shuffle(checkers.begin(), checkers.end(), std::mt19937(std::random_device()()));
        selected_checker = {checkers[0].first, checkers[0].second};
        return selected_checker;
    }
    check_possible_move(checkers, player_num, field);
    std::shuffle(checkers.begin(), checkers.end(), std::mt19937(std::random_device()()));
    selected_checker = {checkers[0].first, checkers[0].second};
    return selected_checker;
}

step_t computer_strategy_t::make_step(const field_t &fld) {
    std::vector<step_t> cells;
    char cell = fld.fld[selected_checker.r][selected_checker.c];
    if (cell == 'W' || cell == 'B') {
        int change_step[2] = {-1, 1};
        for (auto &i: change_step) {
            for (auto &j: change_step) {
                int k = 0;
                while (true) {
                    ++k;
                    int r = selected_checker.r + i * k;
                    int c = selected_checker.c + j * k;
                    if (!check_possible_pos(r, c))
                        break;
                    if (fld.fld[r][c] == '0') {
                        cells.emplace_back(r, c);
                    } else {
                        break;
                    }
                }
            }
        }
    }
    if (cell == 'w') {
        std::vector<std::pair<int, int>> dir = {{-1, -1},
                                                {-1, 1}};
        for (auto d: dir) {
            if (!check_possible_pos(selected_checker.r + d.first, selected_checker.c + d.second))
                continue;
            if (fld.fld[selected_checker.r + d.first][selected_checker.c + d.second] == '0') {
                cells.emplace_back(selected_checker.r + d.first, selected_checker.c + d.second);
            }
        }
    }
    if (cell == 'b') {
        std::vector<std::pair<int, int>> dir = {{1, 1},
                                                {1, -1}};
        for (auto d: dir) {
            if (!check_possible_pos(selected_checker.r + d.first, selected_checker.c + d.second))
                continue;
            if (fld.fld[selected_checker.r + d.first][selected_checker.c + d.second] == '0') {
                cells.emplace_back(selected_checker.r + d.first, selected_checker.c + d.second);
            }
        }
    }

    std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));
    return cells.front();
}

step_t computer_strategy_t::attack_step(const field_t &field) {
    std::vector<step_t> cells;
    char cell = field.fld[selected_checker.r][selected_checker.c];
    if (cell == 'W' || cell == 'B') {
        int change_step[2] = {-1, 1};
        for (auto &i: change_step) {
            for (auto &j: change_step) {
                int k = 0;
                while (true) {
                    ++k;
                    int r = selected_checker.r + i * k;
                    int c = selected_checker.c + j * k;
                    int r_next = r + i;
                    int c_next = c + j;
                    if (!check_possible_pos(r, c) || !check_possible_pos(r_next, c_next))
                        break;
                    if (is_opposite(player_num, field.fld[r][c]) && field.fld[r_next][c_next] == '0') {
                        cells.emplace_back(r_next, c_next);
                        break;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    if (cell == 'w') {
        std::vector<std::pair<int, int>> dir = {{1,  1},
                                                {-1, -1},
                                                {1,  -1},
                                                {-1, 1}};
        for (auto d: dir) {
            if (!check_possible_pos(selected_checker.r + d.first, selected_checker.c + d.second) ||
                !check_possible_pos(selected_checker.r + d.first * 2, selected_checker.c + d.second * 2))
                continue;
            if (is_opposite(player_num, field.fld[selected_checker.r + d.first][selected_checker.c + d.second]) &&
                field.fld[selected_checker.r + d.first * 2][selected_checker.c + d.second * 2] == '0') {
                cells.emplace_back(selected_checker.r + d.first * 2, selected_checker.c + d.second * 2);
            }
        }
    }
    if (cell == 'b') {
        std::vector<std::pair<int, int>> dir = {{1,  1},
                                                {-1, -1},
                                                {1,  -1},
                                                {-1, 1}};
        for (auto d: dir) {
            if (!check_possible_pos(selected_checker.r + d.first, selected_checker.c + d.second) ||
                !check_possible_pos(selected_checker.r + d.first * 2, selected_checker.c + d.second * 2))
                continue;
            if (is_opposite(player_num, field.fld[selected_checker.r + d.first][selected_checker.c + d.second]) &&
                field.fld[selected_checker.r + d.first* 2 ][selected_checker.c + d.second* 2] == '0') {
                cells.emplace_back(selected_checker.r + d.first * 2, selected_checker.c + d.second * 2);
            }
        }
    }
    std::shuffle(cells.begin(), cells.end(), std::mt19937(std::random_device()()));
//    std::cout << cell << " " << selected_checker.r << " " << selected_checker.c << std::endl;
//    std::cout << "Field:" << std::endl;
//    std::cout << " |0|1|2|3|4|5|6|7|" << std::endl;
//
//    int k = 0;
//    for (const auto &line : field.fld) {
//        std::cout << k << '|';
//        for (char c : line) {
//            std::cout << c << '|';
//        }
//        std::cout << std::endl;
//        ++k;
//    }
//    std::cout << "SOSU" << std::endl;
//    std::cout << cells.size() << std::endl;
//    std::cout << "TUT" << std::endl;
    selected_checker = cells.front();

    return selected_checker;
}

void computer_strategy_t::print_stat() const {
    std::cout << "Random model [" << name << "]: " << std::endl;
    computer_interface_t::print_stat();
}




