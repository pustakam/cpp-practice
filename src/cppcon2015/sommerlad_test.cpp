#include <gtest/gtest.h>

#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "sommerlad.hpp"

TEST(Sommerlad, println)
{
    println(std::cout, 1, 2, 3.5f, 'c', "haha");
}

TEST(Sommerlad, arg_visit)
{
    std::vector<int> int_visitor_result;
    auto int_visitor = [&int_visitor_result](const int& arg) -> void {
        int_visitor_result.push_back(arg);
    };
    
    arg_visit(int_visitor, 1, 2, 3);
    ASSERT_TRUE(int_visitor_result == std::vector<int>({1, 2, 3}));

}

TEST(Sommerlad, Sack)
{
    {
    Sack<std::string> s;
    ASSERT_TRUE(s.empty());
    ASSERT_TRUE(s.size() == 0);
    s.putIn("hehe");
    s.putIn("haha");
    ASSERT_TRUE(!s.empty());
    ASSERT_TRUE(s.size() == 2);
    ASSERT_TRUE(s.getOut() == "hehe");
    ASSERT_TRUE(!s.empty());
    ASSERT_TRUE(s.size() == 1);
    ASSERT_TRUE(s.getOut() == "haha");
    ASSERT_TRUE(s.empty());
    }

    {
    Sack<std::string, std::list> s{"hehe", "haha"};
    ASSERT_TRUE(!s.empty());
    ASSERT_TRUE(s.size() == 2);
    ASSERT_TRUE(s.getOut() == "hehe");
    ASSERT_TRUE(!s.empty());
    ASSERT_TRUE(s.size() == 1);
    ASSERT_TRUE(s.getOut() == "haha");
    ASSERT_TRUE(s.empty());
    }
}

