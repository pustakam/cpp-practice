#include <gtest/gtest.h>

#include <iostream>

#include "variadic.hpp"

TEST(Vandevoorde_Variadic, print)
{
    print(1, 2.5f, "hello", 3.677);
    std::cout << '\n';
    printDoubled(1, 2, 3, 4, 5);
    std::cout << '\n';
    printPlus1(1, 2, 3, 4, 5);
    std::cout << '\n';

    std::vector<std::string> laughs{"haha", "hehe", "hoho", "LOL", "XOLOXOLOXO"};

    printElems(laughs, 2, 4, 0);
    std::cout << '\n';

    printIdx<2, 4, 0>(laughs);
    std::cout << '\n';
}

