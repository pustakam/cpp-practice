#ifndef __META_PROGRAMMING_H__
#define __META_PROGRAMMING_H__

constexpr unsigned long fibonacci(unsigned long n)
{
    if (n > 1)
        return fibonacci(n - 1) + fibonacci(n - 2);

    // 0 or 1
    return n;
}

#endif // __META_PROGRAMMING_H__
