#pragma once
#include <concepts>
namespace ugarit
{
    template <typename T>
    concept LessThanCompareable = requires(T t)
    {   
        { t < t} -> std::convertible_to<bool>;
    };

    namespace meta
    {
    
    constexpr bool is_strictly_sorted()
    {
        return true;
    }

    template <LessThanCompareable N>
    constexpr bool is_strictly_sorted(N)
    {
        return true;
    }

    template <LessThanCompareable N>
    constexpr bool is_strictly_sorted(N n1, N n2)
    {
        return n1 < n2;
    }

    template <LessThanCompareable N>
    constexpr bool is_strictly_sorted(N n1, N n2, N ns...)
    {
        return n1 < n2 && is_strictly_sorted(n2, ns);
    }
}
}