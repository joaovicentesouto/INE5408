#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions
#include <stdio.h>
#include <stdlib.h>
#include "array_list.h"
#include <iostream>

int main() {

    structures::ArrayList<int> list{10u};
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    //ASSERT_EQ(5, list.pop(5));
    printf("5 = %d\n", list.pop(5));

    //ASSERT_EQ(6, list.pop(5));
    printf("6 = %d\n", list.pop(5));

    //ASSERT_EQ(8u, list.size());
    printf("8 = %zu\n", list.size());

    //ASSERT_THROW(list.pop(8), std::out_of_range);
    try {
        printf("impri%d\n", list.pop(8));
        printf("%lu\n", list.size());
    } catch (const std::out_of_range& oor) {
        printf("8 = %s\n", oor.what());
    }

    //printf("%d\n", (list.empty()? 1 : 0));
    //printf("%lu\n", list.size());

    //std::size_t w = -1;
    //printf("%zd\n", w);
    //std::cout << w << std::endl;

    return 0;

}
