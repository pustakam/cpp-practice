#ifndef __META_PROGRAMMING_H__
#define __META_PROGRAMMING_H__

#include <type_traits>

constexpr unsigned long fibonacci(unsigned long n)
{
    if (n > 1)
        return fibonacci(n - 1) + fibonacci(n - 2);

    // 0 or 1
    return n;
}

template <typename T>
constexpr T power(const T& x, unsigned int n)
{
    if (n == 0)
        return 1;

    // Using a while loop causes gcc
    // to turn this function into runtime
    return x * power(x, n - 1);
}

template <typename T, typename = std::enable_if<std::is_integral<T>::value>>
constexpr bool is_prime_odd_div(T x, T div)
{
    return div >= x ? true :
        (x % div == 0 ? false : is_prime_odd_div(x, div + 2));
}

template <typename T, typename = std::enable_if<std::is_integral<T>::value>>
constexpr bool is_prime(T x)
{    
    return x == 1 ? false :
        (x % 2 == 0 ? x == 2 : is_prime_odd_div(x, 3)); 
}

#endif // __META_PROGRAMMING_H__
