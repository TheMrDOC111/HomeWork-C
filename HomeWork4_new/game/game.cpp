#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) : field() {
    players.push_back(first);
    first->player_num = 0;
    first->checkers = 12;
    players.push_back(second);
    second->player_num = 1;
    second->checkers = 12;
}

bool game_t::apply_select_step(const step_t &step, std::set<std::pair<int, int>> &checkers, size_t player_num) {
    char &cell = field.fld[step.r][step.c];
    if (cell == '.' || cell == '0' || (checkers.count(std::pair<int, int>(step.r, step.c)) == 0 && !checkers.empty())) {
        return false;
    }

    return !is_opposite(player_num, field.fld[step.r][step.c]);
}

game_t::game_outcome_t game_t::is_win(size_t counter, std::set<std::pair<int, int>> &checkers) const {
    counter = (counter + 1) % 2;
    bool can_make_step = false;
    check_all_checkers(checkers, counter, field);
    if(!checkers.empty())
        can_make_step = true;

    std::vector<std::pair<int, int>> possible_move_checkers;
    check_possible_move(possible_move_checkers, counter, field);

    if(!possible_move_checkers.empty())
        can_make_step = true;

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
    while (is_win(counter, compulsory_checkers) == IN_PROGRESS) {
        counter = (counter + 1) % 2;
        bool is_correct = false;
        while (!is_correct) {
            check_all_checkers(compulsory_checkers, counter, field);
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
                    continue;
                }
            } else {
                do {
                    step_t attack_step = players[counter]->attack_step(field);
                    is_correct = apply_attack_step(select_step, attack_step, counter);
                    if (!is_correct) {
                        players[counter]->on_incorrect_attack_step(attack_step);
                        continue;
                    }
                } while (check_one_checker(select_step, counter, field));
            }
        }
        ++counter_steps;
    }

    if (is_win(counter, compulsory_checkers) == TIE) {
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
    char &select_cell = field.fld[select_step.r][select_step.c];
    char &target_cell = field.fld[target_step.r][target_step.c];
    if (!check_possible_pos(target_step.r, target_step.c))
        return false;
    if (target_cell == '0') {
        if (select_cell == 'w') {
            if ((target_step.r == select_step.r - 1) &&
                ((select_step.c + 1 == target_step.c) || (select_step.c - 1 == target_step.c))) {
                if (target_step.r == 0) {
                    select_cell = 'W';
                }
                std::swap(target_cell, select_cell);
                return true;
            }
        }
        if (select_cell == 'b') {
            if ((target_step.r == select_step.r + 1) &&
                ((select_step.c + 1 == target_step.c) || (select_step.c - 1 == target_step.c))) {
                if (target_step.r == 7) {
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

bool game_t::apply_attack_step(step_t &select_step, step_t &attack_step, size_t player_num) {
    char &attack_cell = field.fld[attack_step.r][attack_step.c];
    char &select_cell = field.fld[select_step.r][select_step.c];
    if (!check_possible_pos(attack_step.r, attack_step.c))
        return false;
    if (attack_cell != '0')
        return false;

    if (select_cell == 'w') {
        if ((abs(attack_step.r - select_step.r) == 2 && abs(attack_step.c - select_step.c) == 2) || (
                attack_step.r - select_step.r == 2 && attack_step.c - select_step.c == 2)) {
            int v_r = (attack_step.r - select_step.r) / abs(attack_step.r - select_step.r);
            int v_c = (attack_step.c - select_step.c) / abs(attack_step.c - select_step.c);
            if (is_opposite(player_num, field.fld[select_step.r + v_r][select_step.c + v_c])) {
                players[1]->checkers -= 1;
                field.fld[select_step.r + v_r][select_step.c + v_c] = '0';
                if (attack_step.r == 0) {
                    select_cell = 'W';
                }
                std::swap(attack_cell, select_cell);
                std::swap(select_step, attack_step);
                return true;
            }
        }
    }
    if (select_cell == 'b') {
        if ((abs(attack_step.r - select_step.r) == 2 && abs(attack_step.c - select_step.c) == 2) || (
                attack_step.r - select_step.r == 2 && attack_step.c - select_step.c == 2)) {
            int v_r = (attack_step.r - select_step.r) / abs(attack_step.r - select_step.r);
            int v_c = (attack_step.c - select_step.c) / abs(attack_step.c - select_step.c);
            if (is_opposite(player_num, field.fld[select_step.r + v_r][select_step.c + v_c])) {
                players[0]->checkers -= 1;
                field.fld[select_step.r + v_r][select_step.c + v_c] = '0';
                if (attack_step.r == 7) {
                    select_cell = 'B';
                }
                std::swap(attack_cell, select_cell);
                std::swap(select_step, attack_step);
                return true;
            }
        }
    }
    if (select_cell == 'W' || select_cell == 'B') {
        if (attack_step.r + attack_step.c == select_step.c + select_step.r ||
            abs(attack_step.r - attack_step.c) == abs(select_step.c - select_step.r)) {
            int v_r = (attack_step.r - select_step.r) / abs(attack_step.r - select_step.r);
            int v_c = (attack_step.c - select_step.c) / abs(attack_step.c - select_step.c);
            int target_r = select_step.r;
            int target_c = select_step.c;
            int enemy_r = 0;
            int enemy_c = 0;
            bool found_enemy = false;
            while (true) {

                target_r += v_r;
                target_c += v_c;

                if (target_r == attack_step.r && target_c == attack_step.c && found_enemy) {
                    players[!is_opposite(player_num, field.fld[target_r][target_c])]->checkers -= 1;
                    field.fld[enemy_r][enemy_c] = '0';
                    std::swap(attack_cell, select_cell);
                    std::swap(select_step, attack_step);
                    return true;
                }

                if (target_r == attack_step.r && target_r == attack_step.c) {
                    break;
                }

                if (!is_opposite(player_num, field.fld[target_r][target_c]) && field.fld[target_r][target_c] != '0') {
                    break;
                }

                if (is_opposite(player_num, field.fld[target_r][target_c]) && found_enemy) {
                    break;
                }
                if (is_opposite(player_num, field.fld[target_r][target_c])) {
                    found_enemy = true;
                    enemy_r = target_r;
                    enemy_c = target_c;
                }
            }
        }
    }

    return false;
}





