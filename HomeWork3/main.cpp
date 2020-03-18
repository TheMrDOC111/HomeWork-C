#include <iostream>
#include "int_list_t.h"

int main() {
    int_list_t list;
    list.push_front(8);
    list.push_front(7);
    list.push_back(44);
    std::cout << "size = " << list.size() << std::endl;
    list.push_front(16);
    list.push_front(22);
    list.push_back(49);

    std::cout << "size = " << list.size() << std::endl;
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list[i] << ',';
    }
    std::cout << std::endl;

    list.insert(5,10000);

    std::cout << "size = " << list.size() << std::endl;
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list[i] << ',';
    }
    std::cout << std::endl;

    int_list_t new_list(list);
    for (int i = 0; i < new_list.size(); ++i) {
        std::cout << new_list[i] << ',';
    }




    return 0;
}
