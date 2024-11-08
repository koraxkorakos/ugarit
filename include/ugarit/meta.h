#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <type_traits>

namespace ugarit
{
    template <bool> struct cond{
        template <typename, typename F> using f = F;
    };

    template <> struct cond<true>{
        template <typename T, typename> using f = T;
    };

    template <typename T> concept arithmetic = std::is_arithmetic_v<T>;


    template <auto... ns> constexpr bool is_homogeneous = false; 
    template <> constexpr bool is_homogeneous<> = true; 
    template <typename T, T... ns> constexpr bool is_homogeneous<ns...> = true; 

    template <auto... ns> constexpr bool is_unique_sorted = false; 
    template <> constexpr bool is_unique_sorted<> = true; 
    template <auto n, auto... ns> constexpr bool is_unique_sorted<n, ns...> 
        = std::ranges::is_sorted(std::initializer_list<decltype(n)>{n, ns...}, std::less_equal<decltype(n)>()); 


    template <auto...ns> 
    struct sequence
    { 
        constexpr static auto size = sizeof...(ns);
    };

    template <auto... ns> 
        requires(is_homogeneous<ns...>)
    using list = sequence<ns...>;        


    template <auto... ns> 
        requires(is_unique_sorted<ns...>)
    using set = list<ns...>;   
}
