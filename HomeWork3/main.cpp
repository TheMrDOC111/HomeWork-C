#include <iostream>
#include "int_list_t.h"

int main() {
    int_list_t l1;
    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    l1.push_back(4);
    l1.reverse();

    std::cout << l1 << std::endl;

    int_list_t l2;

    l2 = l1.splice(1,2);


    std::cout << l2<< std::endl;
    std::cout << l1 << std::endl;


    return 0;
}
