#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) : field() {
    players.push_back(first);
    players.push_back(second);
}

bool game_t::apply_select_step(const step_t &step, size_t player_num) {
    char &cell = field.fld[step.x - 1][step.y - 1];
    if (cell == '.') {
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
    while (is_win() == IN_PROGRESS) {
        counter = (counter + 1) % 2;
        bool is_correct = false;
        while (!is_correct) {
            step_t select_step = players[counter]->select_step(field);
            is_correct = apply_select_step(select_step, counter);
            if (!is_correct) {
                players[counter]->on_incorrect_select_step(select_step);
                continue;
            }
            step_t move_step = players[counter]->make_step(field);
            is_correct = apply_move_step(select_step, move_step, counter);
            if (!is_correct) {
                players[counter]->on_incorrect_move_step(move_step);
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

bool game_t::apply_move_step(const step_t &select_step, const step_t &move_step, size_t player_num) {
    char &cell = field.fld[move_step.x - 1][move_step.y - 1];
    if (cell == '0') {



        std::swap(field.fld[select_step.x - 1][select_step.y - 1], field.fld[move_step.x - 1][move_step.y - 1]);
        return true;
    }
    return false;
}
