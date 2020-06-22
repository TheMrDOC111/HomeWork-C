#pragma once

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

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
                } else {
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

static bool check_possible_pos(int r, int c) {
    return r < 8 && c < 8 && r >= 0 && c >= 0;
}

static bool is_opposite(int player_num, char cell) {
    if (player_num == 0) {
        if (cell == 'b' || cell == 'B') {
            return true;
        }
    }
    if (player_num == 1) {
        if (cell == 'w' || cell == 'W') {
            return true;
        }
    }
    return false;
}


static void check_possible_move(std::vector<std::pair<int, int>> &checkers, size_t player_num, field_t field) {
    checkers.clear();
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (field.fld[row][col] == 'W' || field.fld[row][col] == 'B') {
                if (!is_opposite(player_num, field.fld[row][col])) {
                    std::vector<std::pair<int, int>> dir = {{1,  1},
                                                            {-1, -1},
                                                            {1,  -1},
                                                            {-1, 1}};
                    for (auto d: dir) {
                        if (!check_possible_pos(row + d.first, col + d.second))
                            continue;
                        if (field.fld[row + d.first][col + d.second] == '0') {
                            checkers.emplace_back(row, col);
                            break;
                        }
                    }
                }
            } else if (!is_opposite(player_num, field.fld[row][col])) {
                if (field.fld[row][col] == 'w') {
                    std::vector<std::pair<int, int>> dir = {{-1, -1},
                                                            {-1, 1}};
                    for (auto d: dir) {
                        if (!check_possible_pos(row + d.first, col + d.second))
                            continue;
                        if (field.fld[row + d.first][col + d.second] == '0') {
                            checkers.emplace_back(row, col);
                            break;
                        }
                    }
                }
                if (field.fld[row][col] == 'b') {
                    std::vector<std::pair<int, int>> dir = {{1, 1},
                                                            {1, -1}};
                    for (auto d: dir) {
                        if (!check_possible_pos(row + d.first, col + d.second))
                            continue;
                        if (field.fld[row + d.first][col + d.second] == '0') {
                            checkers.emplace_back(row, col);
                            break;
                        }
                    }
                }
            }
        }
    }
}


static bool check_one_checker(const step_t &select_step, size_t player_num, field_t field) {

    if (field.fld[select_step.r][select_step.c] == 'w' || field.fld[select_step.r][select_step.c] == 'b') {

        std::vector<std::pair<int, int>> dir = {{1,  1},
                                                {-1, -1},
                                                {1,  -1},
                                                {-1, 1}};

        for (auto d: dir) {
            int r = select_step.r + d.first;
            int c = select_step.c + d.second;
            int r_next = r + d.first;
            int c_next = c + d.second;


            if (!check_possible_pos(r, c) || !check_possible_pos(r_next, c_next))
                continue;

//            std::cout << select_step.r << " " << select_step.c << " " << r << " " << c << " " << field.fld[r][c] << " "
//                      << field.fld[r_next][c_next] << std::endl;

            if (is_opposite(player_num, field.fld[r][c]) &&
                field.fld[r_next][c_next] == '0') {
                return true;
            }
        }
    }

    if (field.fld[select_step.r][select_step.c] == 'W' || field.fld[select_step.r][select_step.c] == 'B') {
        int change_step[2] = {-1, 1};
        for (auto &i: change_step) {
            for (auto &j: change_step) {
                int k = 0;
                while (k < 8) {
                    ++k;
                    int r = select_step.r + i * k;
                    int c = select_step.c + j * k;
                    int r_next = r + i;
                    int c_next = c + j;
                    if (!check_possible_pos(r, c) || !check_possible_pos(r_next, c_next))
                        continue;

                    if (!is_opposite(player_num, field.fld[r][c])) //111
                        break;

                    if (is_opposite(player_num, field.fld[r][c]) && is_opposite(player_num, field.fld[r_next][c_next])) //111
                        break;

                    if (is_opposite(player_num, field.fld[r][c]) &&
                        field.fld[r_next][c_next] == '0') {
//                        std::cout << k << " "<< select_step.r << select_step.c << " " << r << c << "XAXAXA" << r_next << c_next
//                                  << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

static void check_all_checkers(std::set<std::pair<int, int>> &checkers, size_t player_num, field_t field) {
    checkers.clear();
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 0) {
                continue;
            }
            if (!is_opposite(player_num, field.fld[r][c]))
                if (check_one_checker(step_t(r, c), player_num, field)) {
                    checkers.insert(std::pair<int, int>(r, c));
                }
        }
    }
}

static void check_all_checkers(std::vector<std::pair<int, int>> &checkers, size_t player_num, field_t field) {
    checkers.clear();
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if ((r + c) % 2 == 0) {
                continue;
            }
            if (!is_opposite(player_num, field.fld[r][c]))
                if (check_one_checker(step_t(r, c), player_num, field)) {
                    checkers.push_back(std::pair<int, int>(r, c));
                }
        }
    }
}




