#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

#include "buffer.hpp"

int testme(int argc, char* argv[])
{
    std::vector<Buffer<int>> buf_vec;
    buf_vec.reserve(8);
    std::cout << "start\n";
    buf_vec.push_back(Buffer<int>{16});
    std::cout << "end push back 1\n";
    buf_vec.push_back(Buffer<int>{32});
    std::cout << "end push back 2\n";
    buf_vec.emplace_back(32);
    std::cout << "end emplace back 3\n";

    buf_vec.insert(buf_vec.begin() + 1, Buffer<int>{64});

    return 0;
}

