#include <iostream>
#include "int_list_t.h"

int main() {
    int_list_t l1;
    for (int i = 0; i < 10; ++i) {
        l1.push_back(i);
    }
    std::cout << l1 << std::endl;
    l1.splice(1, 5);
    int k = l1.size();

//    std::cout << l2 << std::endl;





    return 0;
}
