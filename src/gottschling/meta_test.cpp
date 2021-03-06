#include <gtest/gtest.h>

#include "meta.hpp"

TEST(MetaProgramming, fibonacci)
{
    static_assert(fibonacci(0) == 0, "fibonacci is not compile time");
    static_assert(fibonacci(1) == 1, "fibonacci is not compile time");
    static_assert(fibonacci(2) == 1, "fibonacci is not compile time");
    static_assert(fibonacci(20) == 6765, "fibonacci is not compile time");

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

TEST(MetaProgramming, power)
{
    static_assert(power(0.1, 0) == 1, "power is not compile time");
    static_assert(power(1, 0) == 1, "power is not compile time");
    static_assert(power(2, 0) == 1, "power is not compile time");
    static_assert(power(2, 1) == 2, "power is not compile time");
    static_assert(power(2, 2) == 4, "power is not compile time");
    static_assert(power(2, 5) == 32, "power is not compile time");

    ASSERT_TRUE(power(2, 10) == 1024);
    ASSERT_NEAR(power(0.1, 1), 0.1, 0.01);
    ASSERT_NEAR(power(0.1, 2), 0.01, 0.001);
    ASSERT_NEAR(power(0.1, 3), 0.001, 0.0001);
}

TEST(MetaProgramming, is_prime)
{
    static_assert(!is_prime(1), "is_prime is not compile time");
    static_assert(is_prime(2), "is_prime is not compile time");
    static_assert(is_prime(3), "is_prime is not compile time");
    static_assert(!is_prime(4), "is_prime is not compile time");
    static_assert(is_prime(5), "is_prime is not compile time");
    static_assert(!is_prime(6), "is_prime is not compile time");
    static_assert(is_prime(7), "is_prime is not compile time");
    static_assert(!is_prime(8), "is_prime is not compile time");
    static_assert(!is_prime(9), "is_prime is not compile time");
    static_assert(!is_prime(10), "is_prime is not compile time");

    static_assert(is_prime(103), "is_prime is not compile time");
    static_assert(!is_prime(1003), "is_prime is not compile time");

    ASSERT_TRUE(is_prime(10007));

    // This will not compile since we are checking for integral types
    // ASSERT_TRUE(is_prime(20.5));
}

TEST(MetaProgramming, sum)
{
    ASSERT_TRUE(sum(1) == 1);
    ASSERT_TRUE(sum(1, 2) == 3);
    ASSERT_TRUE(sum(1, 2, 3) == 6);
    ASSERT_TRUE(sum(1, 2, 3, 4) == 10);

    static_assert(std::is_same<decltype(sum(-7, 3.7f, 9u, -2.6)), double>::value,
            "Incorrect sum return type");
    ASSERT_NEAR(sum(-7, 3.7f, 9u, -2.6), 3.1, 0.01);
}

TEST(MetaProgramming, my_is_const)
{
    ASSERT_FALSE(my_is_const<int>::value);
    ASSERT_TRUE(my_is_const<const int>::value);
}

TEST(MetaProgramming, my_conditional)
{
    // gtest macro does not like single parenthesis

    ASSERT_TRUE((std::is_same<typename my_conditional<true, int, double>::type, int>::value));
    ASSERT_TRUE((std::is_same<typename my_conditional<false, int, double>::type, double>::value));
}

TEST(MetaProgramming, fibo)
{
    ASSERT_TRUE(fibo<0>::value == 0);
    ASSERT_TRUE(fibo<1>::value == 1);
    ASSERT_TRUE(fibo<2>::value == 1);
    ASSERT_TRUE(fibo<3>::value == 2);
    ASSERT_TRUE(fibo<4>::value == 3);
    ASSERT_TRUE(fibo<5>::value == 5);
    ASSERT_TRUE(fibo<6>::value == 8);

    ASSERT_TRUE(fibo<11>::value == 89);
    ASSERT_TRUE(fibo<14>::value == 377);
}

