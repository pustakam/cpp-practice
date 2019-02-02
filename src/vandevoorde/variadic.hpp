#ifndef __VANDEVOORDE_VARIADIC_HPP__
#define __VANDEVOORDE_VARIADIC_HPP__

#include <iostream>

void print()
{}

template <typename T, typename... Types>
void print(T firstArg, Types... args)
{
    std::cout << firstArg << '\n';
    print(args...);
}

template <typename... Types>
void printDoubled(Types... args)
{
    print((args + args)...);
}

template <typename... Types>
void printPlus1(Types... args)
{
    print((1 + args)...);
}

template <typename C, typename... TypeIdx>
void printElems(C const& coll, TypeIdx... idx)
{
    print((coll[idx])...);
}

// If we have non type indices template parameter pack
//  then can use that directly in expansion
template <std::size_t... NonTypeIdx, typename C>
void printIdx(C const& coll)
{
    print((coll[NonTypeIdx])...);
}

#endif // __VANDEVOORDE_VARIADIC_HPP__
