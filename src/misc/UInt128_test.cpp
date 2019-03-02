#include <gtest/gtest.h>
#include <cstdint>

#include "UInt128.hpp"

TEST(UInt128, init)
{
    {
    UInt128 a{};
    ASSERT_TRUE(a.lower() == 0);
    ASSERT_TRUE(a.upper() == 0);
    }

    {
    UInt128 b{1};
    ASSERT_TRUE(b.lower() == 1);
    ASSERT_TRUE(b.upper() == 0);
    }

    {
    UInt128 c{UINT64_MAX};
    ASSERT_TRUE(c.lower() == UINT64_MAX);
    ASSERT_TRUE(c.upper() == 0);
    }

    {
    UInt128 c{UINT64_MAX, UINT64_MAX};
    ASSERT_TRUE(c.lower() == UINT64_MAX);
    ASSERT_TRUE(c.upper() == UINT64_MAX);
    }
}

TEST(UInt128, add)
{
    {
        UInt128 a{};
        UInt128 b{1};
        a += b;
        ASSERT_TRUE(a.lower() == 1);
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 a{};
        UInt128 b{UINT64_MAX};
        a += b;
        ASSERT_TRUE(a.lower() == UINT64_MAX);
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 a{1};
        UInt128 b{UINT64_MAX};
        a += b;
        ASSERT_TRUE(a.lower() == 0);
        ASSERT_TRUE(a.upper() == 1);
    }
    {
        UInt128 a{2};
        UInt128 b{UINT64_MAX};
        a += b;
        ASSERT_TRUE(a.lower() == 1);
        ASSERT_TRUE(a.upper() == 1);
    }
    {
        UInt128 a{UINT64_MAX - 1};
        UInt128 b{UINT64_MAX};
        a += b;
        ASSERT_TRUE(a.lower() == UINT64_MAX - 2);
        ASSERT_TRUE(a.upper() == 1);
    }
    {
        UInt128 a{UINT64_MAX};
        UInt128 b{UINT64_MAX};
        a += b;
        ASSERT_TRUE(a.lower() == (UINT64_MAX << 1));
        ASSERT_TRUE(a.upper() == 1);
    }
    {
        UInt128 a(UINT64_MAX, 0);
        UInt128 b(0, UINT64_MAX);
        a += b;
        ASSERT_TRUE(a.lower() == UINT64_MAX);
        ASSERT_TRUE(a.upper() == UINT64_MAX);
    }
    {
        UInt128 a(1, 0);
        UInt128 b(UINT64_MAX - 1, UINT64_MAX);
        a += b;
        ASSERT_TRUE(a.lower() == UINT64_MAX);
        ASSERT_TRUE(a.upper() == UINT64_MAX);
    }
    {
        UInt128 a(1, 1);
        UInt128 b(UINT64_MAX - 1, UINT64_MAX - 1);
        a += b;
        ASSERT_TRUE(a.lower() == UINT64_MAX);
        ASSERT_TRUE(a.upper() == UINT64_MAX);
    }

    //
    // Overflow scenarios
    //
    {
        UInt128 a(UINT64_MAX, UINT64_MAX - 1);
        UInt128 b(UINT64_MAX, UINT64_MAX);
        a += b;
        ASSERT_TRUE(a == UInt128((UINT64_MAX << 1), (UINT64_MAX << 1)));
    }

    {
        UInt128 a(UINT64_MAX, UINT64_MAX);
        UInt128 b(UINT64_MAX, UINT64_MAX);
        a += b;
        ASSERT_TRUE(a.lower() == (UINT64_MAX << 1));
        ASSERT_TRUE(a.upper() == UINT64_MAX);
    }
}

TEST(UInt128, subtract)
{
    {
        UInt128 a{1};
        UInt128 b{};
        a -= b;
        ASSERT_TRUE(a.lower() == 1);
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 b{};
        UInt128 a{UINT64_MAX};
        a -= b;
        ASSERT_TRUE(a.lower() == UINT64_MAX);
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 b{1};
        UInt128 a{UINT64_MAX};
        a -= b;
        ASSERT_TRUE(a.lower() == (UINT64_MAX - 1));
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 b{2};
        UInt128 a{UINT64_MAX};
        a -= b;
        ASSERT_TRUE(a.lower() == (UINT64_MAX - 2));
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 b{UINT64_MAX - 1};
        UInt128 a{UINT64_MAX};
        a -= b;
        ASSERT_TRUE(a.lower() == 1);
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 b{UINT64_MAX};
        UInt128 a{UINT64_MAX};
        a -= b;
        ASSERT_TRUE(a.lower() == 0);
        ASSERT_TRUE(a.upper() == 0);
    }

    {
        UInt128 b(0, UINT64_MAX);
        UInt128 a(UINT64_MAX, UINT64_MAX);
        a -= b;
        ASSERT_TRUE(a.lower() == UINT64_MAX);
        ASSERT_TRUE(a.upper() == 0);
    }

    {
        UInt128 b(1, UINT64_MAX);
        UInt128 a(UINT64_MAX, UINT64_MAX);
        a -= b;
        ASSERT_TRUE(a.lower() == (UINT64_MAX - 1));
        ASSERT_TRUE(a.upper() == 0);
    }

    {
        UInt128 b(UINT64_MAX - 2, UINT64_MAX);
        UInt128 a(UINT64_MAX, UINT64_MAX);
        a -= b;
        ASSERT_TRUE(a.lower() == 2);
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 b(UINT64_MAX - 1, UINT64_MAX);
        UInt128 a(UINT64_MAX, UINT64_MAX);
        a -= b;
        ASSERT_TRUE(a.lower() == 1);
        ASSERT_TRUE(a.upper() == 0);
    }
    {
        UInt128 b(UINT64_MAX, UINT64_MAX);
        UInt128 a(UINT64_MAX, UINT64_MAX);
        a -= b;
        ASSERT_TRUE(a.lower() == 0);
        ASSERT_TRUE(a.upper() == 0);
    }

    //first operand less than second
    {
        UInt128 b(0, 0);
        UInt128 a(1, 0);
        b -= a;
        ASSERT_TRUE(b.lower() == UINT64_MAX);
        ASSERT_TRUE(b.upper() == UINT64_MAX);
    }
    {
        UInt128 b(0, 0);
        UInt128 a(2, 0);
        b -= a;
        ASSERT_TRUE(b.lower() == (UINT64_MAX - 1));
        ASSERT_TRUE(b.upper() == UINT64_MAX);
    }


    {
        UInt128 b(UINT64_MAX - 1, UINT64_MAX);
        UInt128 a(UINT64_MAX, UINT64_MAX);
        b -= a;
        ASSERT_TRUE(b.lower() == UINT64_MAX);
        ASSERT_TRUE(b.upper() == UINT64_MAX);
    }
    {
        UInt128 b(UINT64_MAX - 2, UINT64_MAX);
        UInt128 a(UINT64_MAX, UINT64_MAX);
        b -= a;
        ASSERT_TRUE(b.lower() == UINT64_MAX - 1);
        ASSERT_TRUE(b.upper() == UINT64_MAX);
    }
}

TEST(UInt128, less)
{
    {
        UInt128 a{0};
        UInt128 b{1};
        ASSERT_TRUE(a < b);
        ASSERT_FALSE(b < a);
    }

    {
        UInt128 a(UINT64_MAX, 0);
        UInt128 b(0, UINT64_MAX);
        ASSERT_TRUE(a < b);
        ASSERT_FALSE(b < a);
    }

    {
        UInt128 a(UINT64_MAX - 1, UINT64_MAX);
        UInt128 b(UINT64_MAX, UINT64_MAX);
        ASSERT_TRUE(a < b);
        ASSERT_FALSE(b < a);
    }

    {
        UInt128 a(UINT64_MAX, UINT64_MAX - 1);
        UInt128 b(UINT64_MAX, UINT64_MAX);
        ASSERT_TRUE(a < b);
        ASSERT_FALSE(b < a);
    }

    {
        UInt128 a(UINT64_MAX, UINT64_MAX);
        UInt128 b(UINT64_MAX, UINT64_MAX);
        ASSERT_FALSE(a < b);
        ASSERT_FALSE(b < a);
    }
}

