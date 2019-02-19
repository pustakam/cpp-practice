#ifndef __BUFFER_HPP__
#define __BUFFER_HPP__

#include <algorithm>

template <class T>
class Buffer
{
public:
    Buffer(size_t s)
        : size_{s}, buffer_{new T[s]}
    {
        std::cout << "Buffer constructor\n";
    }
    ~Buffer()
    {
        std::cout << "Buffer destructor ";
        if (buffer_ != nullptr)
        {
            std::cout << "deleting resource ";
            delete [] buffer_;
        }
        std::cout << "\n";
    }
    Buffer(const Buffer& other)
        : size_{other.size_}, buffer_{new T[other.size_]}
    {
        std::cout << "copy constructor\n";
        std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
    }
    Buffer& operator=(const Buffer& other)
    {
        std::cout << "assignment operator\n";
        if (this != &other)
        {
            if (size_ != other.size_)
            {
                delete [] buffer_;
                size_ = other.size_;
                buffer_ = new T[other.size_];
            }
            std::copy(other.buffer_, other.buffer_ + other.size_, buffer_);
        }
        return *this;
    }
    Buffer(Buffer&& other)
        : size_{0}, buffer_{nullptr}
    {
        std::cout << "move constructor\n";
        std::swap(size_, other.size_);
        std::swap(buffer_, other.buffer_);
    }
    Buffer& operator=(Buffer&& other)
    {
        if (this != &other)
        {
            delete [] buffer_;
            size_ = 0;
            buffer_ = nullptr;

            std::swap(size_, other.size_);
            std::swap(buffer_, other.buffer_);
        }
        return *this;
    }

private:
    size_t size_;
    T* buffer_;
};

#endif // __BUFFER_HPP__
