#include <iostream>
#include "int_list_t.h"

int main() {
    int_list_t l3;
    l3.push_back(1);
    l3.push_back(2);
    l3.push_back(3);
    l3.push_back(4);
    l3.push_back(5);
    l3.push_front(6);
    l3.push_front(7);
    int_list_t l1(3, 4);
    l3.true_revers();
    std::cout << l3 << std::endl;




    return 0;
}
