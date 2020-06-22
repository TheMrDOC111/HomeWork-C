#pragma once

#include <string>

#include "../game/structures.h"
#include "computer_interface.h"

class computer_second_strategy_t : public computer_interface_t {
public:
    explicit computer_second_strategy_t(std::string name);

    step_t make_step(const field_t &field) override;

    step_t select_step(const field_t &field) override;

    step_t attack_step(const field_t &field) override;

    void print_stat() const override;

private:
    std::string name;
    step_t selected_checker;

};
