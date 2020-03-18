
#include "safe_long_long_t.h"

safe_long_long_t::safe_long_long_t(long long get_l) {
    l = get_l;
}


safe_long_long_t::safe_long_long_t(safe_long_long_t const &get_l) {
    l = get_l.l;
}

safe_long_long_t::safe_long_long_t() {
    l = 0;
}

long long safe_long_long_t::get_l() const {
    return l;
}

void safe_long_long_t::operator=(const safe_long_long_t &l1) {
    l = l1.l;
}

safe_long_long_t safe_long_long_t::operator++() {
    return safe_long_long_t(++l);
}

safe_long_long_t safe_long_long_t::operator++(int) {
    return safe_long_long_t(l++);
}

safe_long_long_t safe_long_long_t::operator--() {
    return safe_long_long_t(--l);
}

safe_long_long_t safe_long_long_t::operator--(int) {
    return safe_long_long_t(l--);
}

void safe_long_long_t::operator+=(safe_long_long_t l1) {
    l += l1.get_l();
}

void safe_long_long_t::operator-=(safe_long_long_t l1) {
    l -= l1.get_l();
}

void safe_long_long_t::operator*=(safe_long_long_t l1) {
    l *= l1.get_l();
}

void safe_long_long_t::operator/=(safe_long_long_t l1) {
    l /= l1.get_l();
}

void safe_long_long_t::operator%=(safe_long_long_t l1) {
    l %= l1.get_l();
}


safe_long_long_t operator+(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t tmp = l1;
    tmp += l2;
    return tmp;
}

safe_long_long_t operator-(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t tmp = l1;
    tmp -= l2;
    return tmp;
}

safe_long_long_t operator*(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t tmp = l1;
    tmp *= l2;
    return tmp;
}

safe_long_long_t operator/(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t tmp = l1;
    tmp /= l2;
    return tmp;}

safe_long_long_t operator%(safe_long_long_t l1, safe_long_long_t l2) {
    safe_long_long_t tmp = l1;
    tmp %= l2;
    return tmp;}

bool operator==(safe_long_long_t const &l1, safe_long_long_t const &l2) {
    return l1.get_l() == l2.get_l();
}

bool operator!=(safe_long_long_t const &l1, safe_long_long_t const &l2) {
    return !(l1 == l2);
}


std::ostream &operator<<(std::ostream &s, safe_long_long_t l1) {
    s << l1.get_l();
    return s;
}

std::istream &operator>>(std::istream &s, safe_long_long_t &l1) {
    s >> l1;
    return s;
}

bool operator<(safe_long_long_t const &l1, safe_long_long_t const &l2) {
    return l1.get_l() < l2.get_l();
}

bool operator>(safe_long_long_t const &l1, safe_long_long_t const &l2) {
    return l2 < l1;
}

bool operator<=(safe_long_long_t const &l1, safe_long_long_t const &l2) {
    return !(l2 < l1);
}

bool operator>=(safe_long_long_t const &l1, safe_long_long_t const &l2) {
    return !(l1 < l2);
}

