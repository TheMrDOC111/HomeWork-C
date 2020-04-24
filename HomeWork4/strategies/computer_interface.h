#pragma once

#include "interface.h"

class computer_interface_t : public strategy_interface_t {
public:
  computer_interface_t();

  void on_win() override;
  void on_lose() override;
  void on_tie() override;

  void on_incorrect_step(const step_t &step) const override;

  virtual void print_stat() const;

private:
  size_t win_counter;
  size_t lose_counter;
  size_t tie_counter;
};
