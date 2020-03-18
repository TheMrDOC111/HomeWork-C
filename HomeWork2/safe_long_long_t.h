#ifndef NEP_SAFE_LONG_LONG_T_H
#define NEP_SAFE_LONG_LONG_T_H

#include <iostream>

class safe_long_long_t {
private:
    long long l;

public:
    safe_long_long_t(long long get_l);

    safe_long_long_t(safe_long_long_t const &get_l);

    safe_long_long_t();

    long long get_l() const;

    void operator=(const safe_long_long_t &get_l);

    safe_long_long_t operator++();

    safe_long_long_t operator++(int);

    safe_long_long_t operator--();

    safe_long_long_t operator--(int);

    void operator+=(safe_long_long_t l1);

    void operator-=(safe_long_long_t l1);

    void operator*=(safe_long_long_t l1);

    void operator/=(safe_long_long_t l1);

    void operator%=(safe_long_long_t l1);

    ~safe_long_long_t() = default;


};

safe_long_long_t operator+(safe_long_long_t l1, safe_long_long_t l2);

safe_long_long_t operator-(safe_long_long_t l1, safe_long_long_t l2);

safe_long_long_t operator*(safe_long_long_t l1, safe_long_long_t l2);

safe_long_long_t operator/(safe_long_long_t l1, safe_long_long_t l2);

safe_long_long_t operator%(safe_long_long_t l1, safe_long_long_t l2);

bool operator==(safe_long_long_t const &l1, safe_long_long_t const &l2);

bool operator!=(safe_long_long_t const &l1, safe_long_long_t const &l2);

bool operator<(safe_long_long_t const &l1, safe_long_long_t const &l2);

bool operator>(safe_long_long_t const &l1, safe_long_long_t const &l2);

bool operator<=(safe_long_long_t const &l1, safe_long_long_t const &l2);

bool operator>=(safe_long_long_t const &l1, safe_long_long_t const &l2);

std::ostream &operator<<(std::ostream &s, safe_long_long_t l1);

std::istream &operator>>(std::istream &s, safe_long_long_t &l1);

#endif //NEP_SAFE_LONG_LONG_T_H
