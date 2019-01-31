#include <gtest/gtest.h>

#include "meta.hpp"

TEST(MetaProgramming, fibonacci)
{
    ASSERT_TRUE(fibonacci(0) == 0);
    ASSERT_TRUE(fibonacci(1) == 1);
    ASSERT_TRUE(fibonacci(2) == 1);
    ASSERT_TRUE(fibonacci(3) == 2);
    ASSERT_TRUE(fibonacci(4) == 3);
    ASSERT_TRUE(fibonacci(5) == 5);
    ASSERT_TRUE(fibonacci(6) == 8);
    ASSERT_TRUE(fibonacci(7) == 13);
    ASSERT_TRUE(fibonacci(8) == 21);

    ASSERT_TRUE(fibonacci(11) == 89);
    ASSERT_TRUE(fibonacci(14) == 377);
    ASSERT_TRUE(fibonacci(20) == 6765);
}
