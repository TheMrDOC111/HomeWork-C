#include "human.h"

#include <iostream>

void human_strategy_t::on_win() {
    std::cout << name << " - you win!" << std::endl;
}

void human_strategy_t::on_lose() {
    std::cout << name << " - you lose!" << std::endl;
}

void human_strategy_t::on_tie() {
    std::cout << "Tie!" << std::endl;
}

step_t human_strategy_t::make_step(const field_t &fld) {
    std::cout << name << " - type coordinates to move: " << std::endl;
    int x, y;
    std::cin >> x >> y;
    return {x, y};
}

step_t human_strategy_t::select_step(const field_t &field) {
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

    std::cout << name << " - select checker: " << std::endl;
    int x, y;
    std::cin >> x >> y;
    return {x, y};
}

step_t human_strategy_t::attack_step(const field_t &field) {

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

    std::cout << name << " - type coordinates to attack: " << std::endl;
    int x, y;
    std::cin >> x >> y;
    return {x, y};
}

human_strategy_t::human_strategy_t(std::string name) :
        name(std::move(name)) {
    checkers = 12;
}

void human_strategy_t::on_incorrect_move_step(const step_t &step) const {
    std::cout << name << " - incorrect move step: row: " << step.r << "; col: " << step.c << std::endl;
}

void human_strategy_t::on_incorrect_select_step(const step_t &step) const {
    std::cout << name << " - incorrect select step: row: " << step.r << "; col: " << step.c << std::endl;
}

void human_strategy_t::on_incorrect_attack_step(const step_t &step) const {
    std::cout << name << " - incorrect attack step: row: " << step.r << "; col: " << step.c << std::endl;
}

