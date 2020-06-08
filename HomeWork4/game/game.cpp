#include "game.h"
#include <set>

game_t::game_t(const player_t &first, const player_t &second) : field() {
    players.push_back(first);
    first->player_num = 0;
    first->checkers = 12;
    players.push_back(second);
    second->player_num = 1;
    second->checkers = 12;
}

bool game_t::apply_select_step(const step_t &step, std::set<std::pair<int, int>> &checkers, size_t player_num) {
    char &cell = field.fld[step.r - 1][step.c - 1];
    if (cell == '.' || (checkers.count(std::pair<int, int>(step.r - 1, step.c - 1)) == 0 && !checkers.empty())) {
        return false;
    }
    if (player_num == 0 && (cell == 'w' || cell == 'W')) {
        return true;
    } else if (player_num == 1 && (cell == 'b' || cell == 'B')) {
        return true;
    }
    return false;
}

game_t::game_outcome_t game_t::is_win(size_t counter) const {

    counter = (counter + 1) % 2;
    bool can_make_step = false;
    if (counter == 0) {
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
                                    can_make_step = true;
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
                        can_make_step = true;
                    }
                    if ((field.fld[r - 1][c + 1] == 'b' || field.fld[r - 1][c + 1] == 'B') &&
                        (field.fld[r - 2][c + 2] == '0')) { // правый верхний
                        can_make_step = true;
                    }
                    if ((field.fld[r + 1][c - 1] == 'b' || field.fld[r + 1][c - 1] == 'B') &&
                        (field.fld[r + 2][c - 2] == '0')) { // левый нижний
                        can_make_step = true;
                    }
                    if ((field.fld[r + 1][c + 1] == 'b' || field.fld[r + 1][c + 1] == 'B') &&
                        (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                        can_make_step = true;
                    }
                }
            }
        }

        if (!can_make_step) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'W') {
                        if (field.fld[row - 1][col - 1] == '0' || field.fld[row - 1][col + 1] == '0' ||
                            field.fld[row + 1][col - 1] == '0' || field.fld[row + 1][col + 1] == '0') {
                            can_make_step = true;
                        }
                    }
                }
            }
        }

        if (!can_make_step) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'w') {
                        if (field.fld[row - 1][col - 1] == '0' || field.fld[row - 1][col + 1] == '0') {
                            can_make_step = true;
                        }
                    }
                }
            }
        }
    }
    if (counter == 1) {

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
                                    can_make_step = true;
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
                        can_make_step = true;
                    }
                    if ((field.fld[r - 1][c + 1] == 'w' || field.fld[r - 1][c + 1] == 'W') &&
                        (field.fld[r - 2][c + 2] == '0')) { // правый верхний
                        can_make_step = true;
                    }
                    if ((field.fld[r + 1][c - 1] == 'w' || field.fld[r + 1][c - 1] == 'W') &&
                        (field.fld[r + 2][c - 2] == '0')) { // левый нижний
                        can_make_step = true;
                    }
                    if ((field.fld[r + 1][c + 1] == 'w' || field.fld[r + 1][c + 1] == 'W') &&
                        (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                        can_make_step = true;
                    }
                }
            }
        }


        if (!can_make_step) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'B') {
                        if (field.fld[row - 1][col - 1] == '0' || field.fld[row - 1][col + 1] == '0' ||
                            field.fld[row + 1][col - 1] == '0' || field.fld[row + 1][col + 1] == '0') {
                            can_make_step = true;
                        }
                    }
                }
            }
        }

        if (!can_make_step) {
            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (field.fld[row][col] == 'b') {
                        if (field.fld[row + 1][col - 1] == '0' || field.fld[row + 1][col + 1] == '0') {
                            can_make_step = true;
                        }
                    }
                }
            }
        }
    }

    if (!can_make_step)
        return WIN;


    if (counter_steps > 1000) {
        return TIE;
    }

    if (players[0]->checkers == 0 || players[1]->checkers == 0) {
        return WIN;

    }
    return IN_PROGRESS;
}


void game_t::play() {
    size_t counter = 1;
    counter_steps = 0;
    std::set<std::pair<int, int>> compulsory_checkers; // Обязанные бить
    std::set<std::pair<int, int>> compulsory_hit_checkers; // Обязанные быть побитыми

    while (is_win(counter) == IN_PROGRESS) {
        counter = (counter + 1) % 2;
        bool is_correct = false;
        while (!is_correct) {


            check_all_checkers(compulsory_checkers, compulsory_hit_checkers, counter);
            step_t select_step = players[counter]->select_step(field);
            is_correct = apply_select_step(select_step, compulsory_checkers, counter);
            if (!is_correct) {
                players[counter]->on_incorrect_select_step(select_step);
                continue;
            }
            if (compulsory_checkers.empty()) {
                step_t move_step = players[counter]->make_step(field);
                is_correct = apply_move_step(select_step, move_step);
                if (!is_correct) {
                    players[counter]->on_incorrect_move_step(move_step);
                }
            } else {
                int c = 0;
                while (!compulsory_hit_checkers.empty()) {
                    ++c;
                    step_t attack_step = players[counter]->attack_step(field);
                    is_correct = apply_attack_step(select_step, attack_step, compulsory_hit_checkers, counter);
                    if (!is_correct) {
                        std::cout << c  << std:: endl;
                        std::cout << "select: "<< select_step.r << ' ' << select_step.c << std::endl;
                        std::cout << "attack: "<< attack_step.r << ' ' << attack_step.c << std::endl;
                        std::cout << "Field:" << std::endl;
                        std::cout << "X|1|2|3|4|5|6|7|8|X" << std::endl;
                        int k = 1;
                        for (const auto &line : field.fld) {
                            std::cout << k << '|';
                            for (char c : line) {
                                std::cout << c << '|';
                            }
                            std::cout << k << std::endl;
                            ++k;
                        }
                        std::cout << "X|1|2|3|4|5|6|7|8|X" << std::endl;
                        std:: cout << counter << std::endl;

                        players[counter]->on_incorrect_attack_step(attack_step);
                        continue;
                    }
                    compulsory_hit_checkers.clear();
                    check_one_checker(select_step, compulsory_hit_checkers, counter);
                }
            }
        }
        ++counter_steps;
    }
    if (is_win(counter) == TIE) {
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

bool game_t::apply_move_step(const step_t &select_step, const step_t &target_step) {
    char &target_cell = field.fld[target_step.r - 1][target_step.c - 1];
    char &select_cell = field.fld[select_step.r - 1][select_step.c - 1];
    if (target_cell == '0') {
        if (select_cell == 'w') {
            if ((target_step.r == select_step.r - 1) &&
                ((select_step.c + 1 == target_step.c) || (select_step.c - 1 == target_step.c))) {
                if (target_step.r - 1 == 0) {
                    select_cell = 'W';
                }
                std::swap(target_cell, select_cell);
                return true;
            }
        }
        if (select_cell == 'b') {
            if ((target_step.r == select_step.r + 1) &&
                ((select_step.c + 1 == target_step.c) || (select_step.c - 1 == target_step.c))) {
                if (target_step.r - 1 == 7) {
                    select_cell = 'B';
                }
                std::swap(target_cell, select_cell);
                return true;
            }
        }

        if (select_cell == 'W') {
            if (target_step.r + target_step.c == select_step.c + select_step.r ||
                abs(target_step.r - target_step.c) == abs(select_step.c - select_step.r)) {
                std::swap(target_cell, select_cell);
                return true;
            }
        }

        if (select_cell == 'B') {
            if (target_step.r + target_step.c == select_step.c + select_step.r ||
                abs(target_step.r - target_step.c) == abs(select_step.c - select_step.r)) {
                std::swap(target_cell, select_cell);
                return true;
            }
        }


    }
    return false;
}

bool game_t::apply_attack_step(step_t &select_step, step_t &attack_step,
                               std::set<std::pair<int, int>> &must_hit_checkers, size_t player_num) {
    char &attack_cell = field.fld[attack_step.r - 1][attack_step.c - 1];
    char &select_cell = field.fld[select_step.r - 1][select_step.c - 1];
    if (attack_cell == '0') {
        if (player_num == 0) {
            if (select_cell == 'w') {
                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 2, select_step.c - 2)) &&
                    select_step.r - 3 == attack_step.r - 1 && select_step.c - 3 == attack_step.c - 1) {
                    players[1]->checkers -= 1;
                    field.fld[select_step.r - 2][select_step.c - 2] = '0';
                    if (attack_step.r - 1 == 0) {
                        select_cell = 'W';
                    }
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }
                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 2, select_step.c)) &&
                    select_step.r - 3 == attack_step.r - 1 && select_step.c + 1 == attack_step.c - 1) {
                    players[1]->checkers -= 1;
                    field.fld[select_step.r - 2][select_step.c] = '0';
                    if (attack_step.r - 1 == 0) {
                        select_cell = 'W';
                    }
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }

                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 1 + 1, select_step.c - 1 - 1)) &&
                    select_step.r - 1 + 2 == attack_step.r - 1 && select_step.c - 3 == attack_step.c - 1) {
                    players[1]->checkers -= 1;
                    field.fld[select_step.r - 1 + 1][select_step.c - 2] = '0';
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }
                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 1 + 1, select_step.c - 1 + 1)) &&
                    select_step.r - 1 + 2 == attack_step.r - 1 && select_step.c + 1 == attack_step.c - 1) {
                    players[1]->checkers -= 1;
                    field.fld[select_step.r][select_step.c] = '0';
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }

            }
            if (select_cell == 'W') {
                int r = select_step.r - 1;
                int c = select_step.c - 1;
                bool found_enemy = false;
                int enemy_i = -1;
                int enemy_j = -1;

                int i = r;
                int j = c;
                while (i < 8 || j < 8) { // right down
                    ++i;
                    ++j;
                    if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                        break;

                    if ((field.fld[i][j] == 'b' || field.fld[i][j] == 'B') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[1]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }

                }
                found_enemy = false;
                i = r;
                j = c;
                while (i < 8 || j >= 0) { // left down
                    ++i;
                    --j;
                    if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                        break;

                    if ((field.fld[i][j] == 'b' || field.fld[i][j] == 'B') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[1]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }
                }
                found_enemy = false;
                i = r;
                j = c;
                while (i >= 0 || j >= 0) { // left up
                    --i;
                    --j;
                    if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                        break;

                    if ((field.fld[i][j] == 'b' || field.fld[i][j] == 'B') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[1]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }

                }
                found_enemy = false;
                i = r;
                j = c;
                while (i >= 0 || j < 8) { // right up
                    --i;
                    ++j;
                    if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                        break;

                    if ((field.fld[i][j] == 'b' || field.fld[i][j] == 'B') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[1]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }

                }
            }
        } else {
            if (select_cell == 'b') {
                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 2, select_step.c - 2)) &&
                    select_step.r - 3 == attack_step.r - 1 && select_step.c - 3 == attack_step.c - 1) { // левый верхний
                    players[0]->checkers -= 1;
                    field.fld[select_step.r - 2][select_step.c - 2] = '0';
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }

                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 2, select_step.c)) &&
                    select_step.r - 3 == attack_step.r - 1 &&
                    select_step.c + 1 == attack_step.c - 1) {  // правый верхний
                    players[0]->checkers -= 1;
                    field.fld[select_step.r - 2][select_step.c] = '0';
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }

                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 1 + 1, select_step.c - 1 - 1)) &&
                    select_step.r - 1 + 2 == attack_step.r - 1 &&
                    select_step.c - 3 == attack_step.c - 1) { // левый нижний
                    players[0]->checkers -= 1;
                    field.fld[select_step.r - 1 + 1][select_step.c - 2] = '0';
                    if (attack_step.r - 1 == 7) {
                        select_cell = 'B';
                    }
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }
                if (must_hit_checkers.count(std::pair<int, int>(select_step.r - 1 + 1, select_step.c - 1 + 1)) &&
                    select_step.r - 1 + 2 == attack_step.r - 1 &&
                    select_step.c + 1 == attack_step.c - 1) { // правый нижний
                    players[0]->checkers -= 1;
                    field.fld[select_step.r][select_step.c] = '0';
                    if (attack_step.r - 1 == 7) {
                        select_cell = 'B';
                    }
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }
            }
            if (select_cell == 'B') {
                int r = select_step.r - 1;
                int c = select_step.c - 1;
                bool found_enemy = false;
                int enemy_i = -1;
                int enemy_j = -1;

                int i = r;
                int j = c;
                while (i < 8 || j < 8) { // right down
                    ++i;
                    ++j;
                    if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                        break;

                    if ((field.fld[i][j] == 'w' || field.fld[i][j] == 'W') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[0]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }

                }
                found_enemy = false;
                i = r;
                j = c;
                while (i < 8 || j >= 0) { // left down
                    ++i;
                    --j;
                    if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                        break;

                    if ((field.fld[i][j] == 'w' || field.fld[i][j] == 'W') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[0]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }

                }
                found_enemy = false;
                i = r;
                j = c;
                while (i >= 0 || j >= 0) { // left up
                    --i;
                    --j;
                    if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                        break;

                    if ((field.fld[i][j] == 'w' || field.fld[i][j] == 'W') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[0]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }

                }
                found_enemy = false;
                i = r;
                j = c;
                while (i >= 0 || j < 8) { // right up
                    --i;
                    ++j;
                    if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                        break;

                    if ((field.fld[i][j] == 'w' || field.fld[i][j] == 'W') && found_enemy) {
                        break;
                    }

                    if (i == attack_step.r - 1 && j == attack_step.c - 1 && found_enemy) {
                        players[0]->checkers -= 1;
                        field.fld[enemy_i][enemy_j] = '0';
                        std::swap(attack_cell, select_cell);
                        std::swap(select_step, attack_step);
                        return true;
                    }

                    if (must_hit_checkers.count(std::pair<int, int>(i, j))) {
                        found_enemy = true;
                        enemy_i = i;
                        enemy_j = j;
                    }

                }
            }
        }
    }
    return false;
}

void game_t::check_all_checkers(std::set<std::pair<int, int>> &checkers,
                                std::set<std::pair<int, int>> &must_hit_checkers, size_t player_num) {
    checkers.clear();
    must_hit_checkers.clear();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((i + j) % 2 == 0) {
                continue;
            }
            if (check_one_checker(step_t(i + 1, j + 1), must_hit_checkers, player_num)) {
                checkers.insert(std::pair<int, int>(i, j));
            }
        }
    }
}

bool game_t::check_one_checker(const step_t &select_step, std::set<std::pair<int, int>> &must_hit_checkers,
                               size_t player_num) {
    bool flag = false;
    int r = select_step.r - 1;
    int c = select_step.c - 1;

    int i = r;
    int j = c;
    if (player_num == 0) {
        if (field.fld[r][c] == 'w') {
            if ((field.fld[r - 1][c - 1] == 'b' || field.fld[r - 1][c - 1] == 'B') &&
                (field.fld[r - 2][c - 2] == '0')) { // левый верхний
                must_hit_checkers.insert(std::pair<int, int>(r - 1, c - 1));
                flag = true;
            }
            if ((field.fld[r - 1][c + 1] == 'b' || field.fld[r - 1][c + 1] == 'B') &&
                (field.fld[r - 2][c + 2] == '0')) { // правый верхний
                must_hit_checkers.insert(std::pair<int, int>(r - 1, c + 1));
                flag = true;
            }
            if ((field.fld[r + 1][c - 1] == 'b' || field.fld[r + 1][c - 1] == 'B') &&
                (field.fld[r + 2][c - 2] == '0')) { // левый нижний
                must_hit_checkers.insert(std::pair<int, int>(r + 1, c - 1));
                flag = true;
            }
            if ((field.fld[r + 1][c + 1] == 'b' || field.fld[r + 1][c + 1] == 'B') &&
                (field.fld[r + 2][c + 2] == '0')) { // правый нижний
                must_hit_checkers.insert(std::pair<int, int>(r + 1, c + 1));
                flag = true;
            }
        }

        if (field.fld[r][c] == 'W') {
            while (i < 8 || j < 8) { // right down
                ++i;
                ++j;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    break;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    if (field.fld[i + 1][j + 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
            i = r;
            j = c;
            while (i < 8 || j >= 0) { // left down
                ++i;
                --j;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    break;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    if (field.fld[i + 1][j - 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
            i = r;
            j = c;
            while (i >= 0 || j >= 0) { // left up
                --i;
                --j;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    break;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    if (field.fld[i - 1][j - 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
            i = r;
            j = c;
            while (i >= 0 || j < 8) { // right up
                --i;
                ++j;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    break;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    if (field.fld[i - 1][j + 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
        }
    } else {
        if (field.fld[r][c] == 'b') {
            if ((field.fld[r - 1][c - 1] == 'w' || field.fld[r - 1][c - 1] == 'W') &&
                (field.fld[r - 2][c - 2] == '0')) {// левый верхний
                must_hit_checkers.insert(std::pair<int, int>(r - 1, c - 1));
                flag = true;
            }
            if ((field.fld[r - 1][c + 1] == 'w' || field.fld[r - 1][c + 1] == 'W') &&
                (field.fld[r - 2][c + 2] == '0')) {// правый верхний

                must_hit_checkers.insert(std::pair<int, int>(r - 1, c + 1));
                flag = true;
            }
            if ((field.fld[r + 1][c - 1] == 'w' || field.fld[r + 1][c - 1] == 'W') &&
                (field.fld[r + 2][c - 2] == '0')) {// левый нижний
                must_hit_checkers.insert(std::pair<int, int>(r + 1, c - 1));
                flag = true;
            }
            if ((field.fld[r + 1][c + 1] == 'w' || field.fld[r + 1][c + 1] == 'W') &&
                (field.fld[r + 2][c + 2] == '0')) {// правый нижний
                must_hit_checkers.insert(std::pair<int, int>(r + 1, c + 1));
                flag = true;
            }
        }
        if (field.fld[r][c] == 'B') {
            while (i < 8 || j < 8) { // right down
                ++i;
                ++j;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    break;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    if (field.fld[i + 1][j + 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
            i = r;
            j = c;
            while (i < 8 || j >= 0) { // left down
                ++i;
                --j;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    break;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    if (field.fld[i + 1][j - 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
            i = r;
            j = c;
            while (i >= 0 || j >= 0) { // left up
                --i;
                --j;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    break;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    if (field.fld[i - 1][j - 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
            i = r;
            j = c;
            while (i >= 0 || j < 8) { // right up
                --i;
                ++j;
                if (field.fld[i][j] == 'b' || field.fld[i][j] == 'B')
                    break;
                if (field.fld[i][j] == 'w' || field.fld[i][j] == 'W')
                    if (field.fld[i - 1][j + 1] == '0') {
                        must_hit_checkers.insert(std::pair<int, int>(i, j));
                        flag = true;
                        break;
                    } else {
                        break;
                    }

            }
        }
    }
    return flag;
}

