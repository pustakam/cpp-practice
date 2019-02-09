#include <type_traits>

#include <gtest/gtest.h>

#include "oop.hpp"

TEST(OOProgramming, PointCRTP)
{
    Point p1(1, 2);
    Point p2(1, 2);
    Point p3(1, 3);
    ASSERT_TRUE(p1 == p2);
    ASSERT_TRUE(p1 != p3);
    static_assert(std::is_same<decltype(p1.clone()), Point*>::value, "Clone bad");
}

