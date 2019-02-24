#include <iostream>
#include <iomanip>
#include <string>
#include <thread>
#include <chrono>
#include <algorithm>

#include "queue.hpp"

using namespace std::chrono_literals;

enum class MsgType
{
    data,
    end
};
std::ostream& operator<<(std::ostream& os, MsgType t)
{
    switch(t)
    {
        case MsgType::data: os << "MsgType::data"; break;
        case MsgType::end: os << "MsgType::end"; break;
        default: os << "Invalid MsgType"; break;
    }
    return os;
}

struct Msg
{
    MsgType type = MsgType::end;
    int data;
};
std::ostream& operator<<(std::ostream& os, const Msg& m)
{
    os << "{" << "type=" << m.type << " data=" << m.data << "}";
    return os;
}

void producer(Queue<Msg>& q, const int iterations, const int id)
{
    std::cout << "producer=" << id << ", starting" << std::endl;
    for (int j=0; j < iterations; ++j)
    {
        const Msg m{MsgType::data, j};
        std::cout << "producer=" << id << ", message= " << m << std::endl;
        q.push(m);
        std::this_thread::sleep_for(1s);
    }
    std::cout << "producer=" << id << ", exiting" << std::endl;
}

void consumer(Queue<Msg>& q, const int id)
{
    std::cout << "consumer=" << id << ", starting" << std::endl;
    while(true)
    {
        Msg m;
        if (!q.try_pop(m)) // suboptimal, but test try_pop
            q.wait_and_pop(m);
        std::cout << "consumer=" << id << ", message= " << m << std::endl;
        if (m.type == MsgType::end)
            break;
        std::this_thread::sleep_for(1s);
    }
    std::cout << "consumer=" << id << ", exiting" << std::endl;
}

static int testme()
{
    Queue<Msg> q;
    using vector_t = std::vector<std::thread>;
    vector_t consumers, producers;
    const int iterations{10};
    for (vector_t::size_type i=0; i<1; ++i)
    {
        consumers.push_back(std::thread([&q, i]{return consumer(q, i);}));
    }
    std::this_thread::sleep_for(1s);
    for (vector_t::size_type i=0; i<1; ++i)
    {
        producers.push_back(std::thread([&q, i]{return producer(q, iterations, i);}));
    }
    std::for_each(producers.begin(), producers.end(), [](std::thread& t){t.join();});
    for (vector_t::size_type i=0; i<consumers.size(); ++i)
    {
        q.push({MsgType::end, 0});
    }
    std::for_each(consumers.begin(), consumers.end(), [](std::thread& t){t.join();});

    return 0;
}

