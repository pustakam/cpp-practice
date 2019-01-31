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

template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
constexpr bool is_prime_odd_div(T x, T div)
{
    return div >= x ? true :
        (x % div == 0 ? false : is_prime_odd_div(x, div + 2));
}

// If T is not integral then SFINAE removes this function 
// from the set of functions
template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
constexpr bool is_prime(T x)
{    
    return x == 1 ? false :
        (x % 2 == 0 ? x == 2 : is_prime_odd_div(x, 3)); 
}

// sum_type is the return type of sum

template <typename... P>
struct sum_type {};

// Specialization for single type
template <typename T>
struct sum_type<T>
{
    using type = T;
};
// Specialization for more than 1 type
template <typename T, typename... P>
struct sum_type<T, P...>
{
    using type = decltype(T() + typename sum_type<P...>::type());
};

template <typename... P>
using sum_type_t = typename sum_type<P...>::type;

template <typename T>
sum_type_t<T> sum(T t)
{
    return t;
}
template <typename T, typename... P>
sum_type_t<T, P...> sum(T t, P... p)
{
    return t + sum(p...);
}

template <typename T>
struct my_is_const : std::false_type
{
    // static constexpr bool value = false;
};

template <typename T>
struct my_is_const<const T> : std::true_type
{
    // static constexpr bool value = true;
};

template <bool Condition, typename ThenType, typename ElseType>
struct my_conditional
{
    using type = ThenType;
};
template <typename ThenType, typename ElseType>
struct my_conditional<false, ThenType, ElseType>
{
    using type = ElseType;
};

// Well formed (has member type) only if Condition true
template <bool Condition, typename T = void>
struct my_enable_if
{
    using type = T;
};
template <typename T>
struct my_enable_if<false, T>
{};

template <unsigned long n>
struct fibo
{
    static constexpr unsigned long value = fibo<n - 1>::value + fibo<n - 2>::value; 
};
template<>
struct fibo<0>
{
    static constexpr unsigned long value = 0;
};
template<>
struct fibo<1>
{
    static constexpr unsigned long value = 1;
};

#endif // __META_PROGRAMMING_H__
