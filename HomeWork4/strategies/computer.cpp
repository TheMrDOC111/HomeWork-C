#include "computer.h"

#include <cassert>
#include <iostream>
#include <vector>


computer_strategy_t::computer_strategy_t(std::string name) :
        name(std::move(name)) {
    checkers = 12;
}

step_t computer_strategy_t::select_step(const field_t &field) {

    return step_t(0, 0);
}

step_t computer_strategy_t::make_step(const field_t &fld) {
    return step_t(0, 0);
}

step_t computer_strategy_t::attack_step(const field_t &field) {
    return step_t(0, 0);
}

void computer_strategy_t::print_stat() const {
    std::cout << "Random model [" << name << "]: " << std::endl;
    computer_interface_t::print_stat();
}




