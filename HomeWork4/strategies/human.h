#pragma once
#include "interface.h"

class human_strategy_t : public strategy_interface_t {
public:
    human_strategy_t();

    step_t select_step(const field_t &field) override;

    step_t make_step(const field_t &field) override;

    void on_incorrect_select_step(const step_t &step) const override;
    void on_incorrect_move_step(const step_t &step) const override;

    void on_win() override;

    void on_lose() override;

    void on_tie() override;
};
