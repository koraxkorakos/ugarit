#pragma once
#include <cstdint>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <ugarit/meta.h>
#include <utility>

namespace ugarit
{
#if 0
    template <integral_type T, T... ns> 
       requires(std::ranges::is_sorted(std::initializer_list<T>{ns...}, std::less_equal<T>{}))
    using integer_set = std::integer_sequence<ns...>;

    struct union
    {
        template <typename T, typename...> struct f;
        template <typename T> struct f<> { using type = integer_set<T>; };
        template <typename T, T... ns> struct f<>
        {
            using type = <integer_set<T, ns...>> = integer_set<T, ns...>;
        };
        template <typename T, T... ns1, T... ns2> struct f<integer_set<T, ns1...>, integer_set<T, ns2...>> 
            = TODO;
        template <typename T1, typename T2, typename...Ts> struct f<T1, T2, Ts...> 
            = typename union::template f<T, typename union::template<union<T1, T2>::template f, Ts...>;            
    };

    template <typename... Ts> using union_t = union::template f<Ts...>;


       requires(std::ranges::is_sorted(std::initializer_list<T>{ns...}, std::less_equal<T>{}))
    using integer_set = std::integer_sequence<ns...>;



    template <integral_type T, T... ns> 
       requires(std::ranges::is_sorted(std::initializer_list<T>{ns...}, std::less_equal<T>{}))
    struct integer_set{
       using vale_type = T; 
       consteval auto size = sizeof...(ns);
    };

    using sparse_index = std::uintmax_t;

    template <std::size_t... ns> using index_set = integer_set<std::size_t, ns...>;
    template <std::size_t... ns> using sparse_index_set = integer_set<sparse_index, ns...>;

    template <typename T, typename A, typename B> struct set_union;
    template <typename T, T...ns1, T...ns2> struct set_union<integer_set<T,ns1...>,integer_set<T,ns2...>>
    {
       static constexpr auto pair = [](){
            std::array<T, sizeof...(ns1) + sizeof...(ns2...)> arr{ ns1..., ns2... };
            std::inplace_merge(arr.begin(), arr.begin() + sizeof...(ns1), arr.end());
            auto const sorted_size = std::unique(arr.begin(), arr.end()) - arr.begin();
            return std::make_pair(arr, sorted_size); }();
        template <typename> struct helper;
        template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
        {
            using type = std::integer_sequence<T, pair.first[ms]...>;
        };
        using type = typename helper<std::make_index_sequence<pair.second>>::type;
    };

    template <typename... Ts> struct set_union_t;
    template <typename T> struct set_union_t<T>{ using type = T; };

    template <typename A, typename B, typename... Ts> 
    struct set_union_t = set_union<typename set_union<A,B>::type, Ts...>;
 #endif

}