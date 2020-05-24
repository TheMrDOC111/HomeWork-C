#include "game.h"
#include <unordered_set>
#include <set>

game_t::game_t(const player_t &first, const player_t &second) : field() {
    players.push_back(first);
    players.push_back(second);
}

bool
game_t::apply_select_step(const step_t &step, std::set<std::pair<int, int>> &checkers, size_t player_num) {
    char &cell = field.fld[step.x - 1][step.y - 1];
    if (cell == '.' || (checkers.count(std::pair<int, int>(step.x - 1, step.y - 1)) == 0 && !checkers.empty())) {
        return false;
    }
    std::cout << player_num << " - target checker: " << cell << std::endl;
    if (player_num == 0 && (cell == 'w' || cell == 'W')) {
        return true;
    } else if (player_num == 1 && (cell == 'b' || cell == 'B')) {
        return true;
    }
    return false;
}

game_t::game_outcome_t game_t::is_win() const {

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

    while (is_win() == IN_PROGRESS) {
        counter = (counter + 1) % 2;
        bool is_correct = false;
        check_checkers(compulsory_checkers, compulsory_hit_checkers, counter);
        while (!is_correct) {
            std::cout << "Must hit size - " << compulsory_checkers.size() << std::endl;
            step_t select_step = players[counter]->select_step(field);
            is_correct = apply_select_step(select_step, compulsory_checkers, counter);
            if (!is_correct) {
                players[counter]->on_incorrect_select_step(select_step);
                continue;
            }
            if (compulsory_checkers.empty()) {
                step_t move_step = players[counter]->make_step(field);
                is_correct = apply_move_step(select_step, move_step, counter);
                if (!is_correct) {
                    players[counter]->on_incorrect_move_step(move_step);
                }
            } else {
                // Туть цикл для проверки шашек которые мы обязаны побить одной выбранной шашкой
                while (!compulsory_hit_checkers.empty()) {
                    step_t attack_step = players[counter]->attack_step(field);
                    is_correct = apply_attack_step(select_step, attack_step, counter);
                    if (!is_correct) {
                        players[counter]->on_incorrect_attack_step(attack_step);
                        continue;
                    }
                    check_checkers(compulsory_checkers, compulsory_hit_checkers, counter);
                }
                // туть конец цикла
            }

        }
        ++counter_steps;
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

bool game_t::apply_move_step(const step_t &select_step, const step_t &target_step, size_t player_num) {
    char &target_cell = field.fld[target_step.x - 1][target_step.y - 1];
    char &select_cell = field.fld[select_step.x - 1][select_step.y - 1];
    if (target_cell == '0') {
        if (select_cell == 'w') {
            if ((target_step.x == select_step.x - 1) &&
                ((select_step.y + 1 == target_step.y) || (select_step.y - 1 == target_step.y))) {
                std::swap(target_cell, select_cell);
                return true;
            }
        }
        if (select_cell == 'b') {
            if ((target_step.x == select_step.x + 1) &&
                ((select_step.y + 1 == target_step.y) || (select_step.y - 1 == target_step.y))) {
                std::swap(target_cell, select_cell);
                return true;
            }
        }

    }
    return false;
}

void game_t::check_checkers(std::set<std::pair<int, int>> &checkers,
                            std::set<std::pair<int, int>> &must_hit_checkers, size_t player_num) {
    checkers.clear();
    must_hit_checkers.clear();
    if (player_num == 0) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (field.fld[i][j] == 'w') {
                    if (i - 2 >= 0) {
                        if (j - 2 >= 0) {
                            if ((field.fld[i - 1][j - 1] == 'b' || field.fld[i - 1][j - 1] == 'B') &&
                                (field.fld[i - 2][j - 2] == '0')) {
                                checkers.insert(std::pair<int, int>(i, j));
                                must_hit_checkers.insert(std::pair<int, int>(i - 1, j - 1));
                            }
                        }
                        if (j + 2 < 8) {
                            if ((field.fld[i - 1][j + 1] == 'b' || field.fld[i - 1][j + 1] == 'B') &&
                                (field.fld[i - 2][j + 2] == '0')) {
                                checkers.insert(std::pair<int, int>(i, j));
                                must_hit_checkers.insert(std::pair<int, int>(i - 1, j + 1));
                            }
                        }
                    }
                }

            }
        }
    } else {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (field.fld[i][j] == 'b') {
                    if (i + 2 < 8) {
                        if (j - 2 >= 0) {
                            if ((field.fld[i + 1][j - 1] == 'w' || field.fld[i + 1][j - 1] == 'W') &&
                                (field.fld[i + 2][j - 2] == '0')) {
                                checkers.insert(std::pair<int, int>(i, j));
                                must_hit_checkers.insert(std::pair<int, int>(i + 1, j - 1));
                            }
                        }
                        if (j + 2 < 8) {
                            if ((field.fld[i + 1][j + 1] == 'w' || field.fld[i - 1][j + 1] == 'W') &&
                                (field.fld[i + 2][j + 2] == '0')) {
                                checkers.insert(std::pair<int, int>(i, j));
                                must_hit_checkers.insert(std::pair<int, int>(i + 1, j + 1));
                            }
                        }
                    }
                }
            }
        }
    }

}

bool game_t::apply_attack_step(const step_t &select_step, const step_t &attack_step, size_t player_num) {
    return false;
}
