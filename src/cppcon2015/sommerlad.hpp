#ifndef __CPPCON2015__SOMMERLAD_HPP__
#define __CPPCON2015__SOMMERLAD_HPP__

#include <ostream>
#include <vector>
#include <array>
#include <initializer_list>
#include <utility>
#include <tuple>

// base case
void println(std::ostream& out)
{
    out << "\n";
}
// general case
template <typename Head, typename... Tail>
void println(std::ostream& out, const Head& head, const Tail&... tail)
{
    out << head;
    if (sizeof...(tail))
    {
        out << ", ";
    }
    println(out, tail...);
}

// base case
// Specification of base case depends on context,
//  does not have to be empty always
template <typename V, typename Head>
void arg_visit(V& visitor, const Head& head)
{
    visitor(head);
}
// general case
template <typename V, typename Head, typename... Tail>
void arg_visit(V& visitor, const Head& head, const Tail&... tail)
{
    visitor(head);
    arg_visit(visitor, tail...);
}

template <typename T,
         template <typename...> class container=std::vector>
class Sack
{
    using SackType = container<T>;
    using size_type = typename SackType::size_type;

public:
    Sack()
        : sack{}
    {}
    Sack(std::initializer_list<T> l)
        : sack(l)
    {}
    ~Sack() = default;
    Sack(const Sack&) = default;
    Sack& operator=(const Sack&) = default;
    Sack(Sack&&) = default;
    Sack& operator=(Sack&&) = default;

    bool empty() const
    {
        return sack.empty();
    }
    size_type size() const
    {
        return sack.size();
    }
    void putIn(const T& item)
    {
        sack.push_back(item);
    }

    T getOut(); 

private:
    SackType sack;
};

template <typename T,
         template <typename...> class container>
T Sack<T, container>::getOut()
{
    if (sack.empty())
        throw std::logic_error("Sack empty");

    // Usually we take a random item out, but here we just use remove the first
    T retval{sack.front()};
    sack.erase(sack.begin());
    return retval;
}

// Deduce the indices as a parameter pack
//  from the input index_sequence
template <typename A, std::size_t... NonTypeIdx>
auto array_to_tuple_impl(const A& a, std::index_sequence<NonTypeIdx...>)
{
    return std::make_tuple((a[NonTypeIdx])...);
}

// Deduce N from input array
//  and use it to make the int seq 0 to N-1
template <typename T, std::size_t N>
auto array_to_tuple(const std::array<T, N>& a)
{
    auto int_seq = std::make_index_sequence<N>{};
    return array_to_tuple_impl(a, int_seq);
}

#endif // __CPPCON2015__SOMMERLAD_HPP__
