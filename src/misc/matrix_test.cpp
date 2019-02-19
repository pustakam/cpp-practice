#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

#include "matrix.hpp"

int testme(int argc, char* argv[])
{
    Matrix<double, 5, 10> m1{3};
    /*
    auto m2 = m1 + 1;
    std::cout << m2 << std::endl;
    std::cout << m2 - 1 << std::endl;
    m2 = m2*2;
    std::cout << m2 << std::endl;
    std::cout << m2/2 << std::endl;
    Matrix<double, 10, 4> m9{2};
    std::cout << m1*m9 << std::endl;
    */
    /*
    std::cout << m1 << std::endl;
    std::cout << m1.transpose() << std::endl;
    std::cout << m1 * m1.transpose() << std::endl;
    */
    return 0;
}

