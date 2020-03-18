#include "safe_long_long_t.h"
#include "safe_c_array_t.tpp"

int main() {
    safe_c_array_t<int> array(10);
    array[1] = 1000;
    array[2] = 2000;
    safe_c_array_t<int> test(4);
    test = test;
    return 0;
}
