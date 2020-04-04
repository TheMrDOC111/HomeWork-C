#include <iostream>
#include "int_list_t.h"

int main() {
    int_list_t l3;
    l3.push_back(1);
    l3.push_back(2);
    l3.push_front(6);
    l3.push_front(7);
    int_list_t l4(4,4);
    l4.reverse();
    std:: cout << l4.merge(l3) << std::endl;
    l3.reverse();
    std:: cout << l3;





    return 0;
}
