#pragma once

#include <memory>
#include <vector>
#include <unordered_set>
#include <set>

#include "../strategies/interface.h"
#include "structures.h"

class game_t {
public:
    using player_t = std::shared_ptr<strategy_interface_t>;

    game_t(const player_t &first, const player_t &second);

    void play();

private:
    enum game_outcome_t {
        WIN,
        TIE,
        IN_PROGRESS
    };

    game_outcome_t is_win(size_t counter, std::set<std::pair<int, int>> &checkers) const;

    bool apply_select_step(const step_t &step, std::set<std::pair<int, int>> &checkers, size_t player_num);

    bool apply_move_step(const step_t &select_step, const step_t &target_step);

    bool apply_attack_step(step_t &select_step, step_t &attack_step, size_t player_num);


    field_t field;
    std::vector<player_t> players;
    size_t counter_steps{};
};

