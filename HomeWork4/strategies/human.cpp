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
    int r;
    char c;
    std::cin >> c >> r;
    return {r, ((int)c-64)};
}

step_t human_strategy_t::select_step(const field_t &field) {
    std::cout << "Field:" << std::endl;
    std::cout << "X|A|B|C|D|E|F|G|H|X" << std::endl;
    int k = 1;
    for (const auto &line : field.fld) {
        std::cout << k << '|';
        for (char c : line) {
            std::cout << c << '|';
        }
        std::cout << k << std::endl;
        ++k;
    }
    std::cout << "X|A|B|C|D|E|F|G|H|X" << std::endl;



    std::cout << name << " - select checker: " << std::endl;
    int r;
    char c;
    std::cin >> c >> r;
    return {r, ((int)c-64)};
}

step_t human_strategy_t::attack_step(const field_t &field) {

    std::cout << "Field:" << std::endl;
    std::cout << "X|A|B|C|D|E|F|G|H|X" << std::endl;

    int k = 1;
    for (const auto &line : field.fld) {
        std::cout << k << '|';
        for (char c : line) {
            std::cout << c << '|';
        }
        std::cout << k << std::endl;
        ++k;
    }
    std::cout << "X|A|B|C|D|E|F|G|H|X" << std::endl;




    std::cout << name << " - type coordinates to attack: " << std::endl;
    int r;
    char c;
    std::cin >> c >> r;
    return {r, ((int)c-64)};
}

human_strategy_t::human_strategy_t(std::string name) :
        name(std::move(name)) {
}

void human_strategy_t::on_incorrect_move_step(const step_t &step) const {
    std::cout << name << " - incorrect move step: row: " << step.c << "; col: " << step.r << std::endl;
}

void human_strategy_t::on_incorrect_select_step(const step_t &step) const {
    std::cout << name << " - incorrect select step: row: " << step.c << "; col: " << step.r << std::endl;
}

void human_strategy_t::on_incorrect_attack_step(const step_t &step) const {
    std::cout << name << " - incorrect attack step: row: " << step.c << "; col: " << step.r << std::endl;
}

