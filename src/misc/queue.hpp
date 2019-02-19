#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename Data>
class Queue
{
public:
    void push(Data const& data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_queue.push(data);
        // Avoid the case where consumer wakes up with mutex locked
        lock.unlock();
        m_condition_variable.notify_one();
    }

    bool empty() const
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    bool try_pop(Data& data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_queue.empty())
        {
            return false;
        }
        data = m_queue.front();
        m_queue.pop();
        return true;
    }

    void wait_and_pop(Data& data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition_variable.wait(lock, [this] { return !this->m_queue.empty(); });
        data = m_queue.front();
        m_queue.pop();
    }

public:
    Queue() = default;
    ~Queue() = default;
    Queue(Queue const& other) = delete;
    Queue& operator=(Queue const& other) = delete;
    Queue(Queue&& other) = delete;
    Queue& operator=(Queue&& other) = delete;

private:
    std::queue<Data> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_condition_variable;
};

#endif // __QUEUE_HPP__
