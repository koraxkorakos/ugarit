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

    template <typename...> struct set_union;
    template <typename...> struct set_intersection;
    template <typename...> struct set_difference;
    template <typename...> struct set_symmetric_difference;    

    template <typename... Ts> using set_union_t = typename set_union::template<Ts...>f::type;
    template <typename... Ts> using set_intersection_t = typename set_intersection::template<Ts...>f::type;
    template <typename... Ts> using set_difference_t = typename set_difference::template<Ts...>f::type;
    template <typename... Ts> using set_symmetric_difference_t = typename set_symmetric_difference::template<Ts...>f::type;    

    template <> struct set_union<>{ using type = sequence<>; };
    template <> struct set_intersection<>{ using type = sequence<>; };
    template <> struct set_difference<>{ using type = sequence<>; };
    template <> struct set_symmetric_difference<>{ using type = sequence<>; };

    template <typename T1, typename T2, typename... Ts> struct set_union<T1,T2,Ts...>{
         using type = set_union_t<set_union_t<T1, T2>, Ts...>; 
    };
    template <typename T1, typename T2, typename... Ts> struct set_intersection<T1,T2,Ts...>{
         using type = set_intersection<set_uniset_intersectionon_t<T1, T2>, Ts...>; 
    };
    template <typename T1, typename T2, typename... Ts> struct set_difference<T1,T2,Ts...>{
         using type = set_difference<set_difference<T1, T2>, Ts...>; 
    };
    template <typename T1, typename T2, typename... Ts> struct set_symmetric_difference<T1,T2,Ts...>{
         using type = set_symmetric_difference<set_symmetric_difference<T1, T2>, Ts...>; 
    };

    template <auto... ns1, auto... ns2> struct set_union<set<ns1...>, set<ns2...>>
    {
        static constexpr auto pair = [](){
            std::array<T, sizeof...(ns1) + sizeof...(ns2)> arr{ ns1..., ns2... };
            std::merge_inplace(arr.begin(), arr.begin() + sizeof...(ns1), arr.end());
            auto const sorted_size = std::unique(arr.begin(), arr.end()) - arr.begin();
            return std::make_pair(arr, sorted_size); }();
        template <typename> struct helper;
        template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
        {
            using type = std::integer_sequence<T, pair.first[ms]...>;
        };
        using type = typename helper<std::make_index_sequence<pair.second>>::type;
    };

    template <auto... ns1, auto... ns2> struct set_intersection<set<ns1...>, set<ns2...>>
    {
        static constexpr auto pair = [](){
            std::array<T, sizeof...(ns1)> arr1{ ns1...};
            std::array<T, sizeof...(ns2)> arr2{ ns2...};
            std::array<T, std::min(sizeof...(ns1), sizeof...(ns2))> arr;            
            auto const sorted_size = std::set_intersection(arr1.begin(), arr1.begin(), arr2.begin(), arr3.begin(), arr.begin())
               - arr.begin();
            return std::make_pair(arr, sorted_size); }();
        template <typename> struct helper;
        template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
        {
            using type = std::integer_sequence<T, pair.first[ms]...>;
        };
        using type = typename helper<std::make_index_sequence<pair.second>>::type;
    };

    template <auto... ns1, auto... ns2> struct set_difference<set<ns1...>, set<ns2...>>
    {
        static constexpr auto pair = [](){
            std::array<T, sizeof...(ns1)> arr1{ ns1...};
            std::array<T, sizeof...(ns2)> arr2{ ns2...};
            std::array<T, sizeof...(ns1)> arr;            
            auto const sorted_size = std::set_difference(arr1.begin(), arr1.begin(), arr2.begin(), arr3.begin(), arr.begin())
               - arr.begin();
            return std::make_pair(arr, sorted_size); }();
        template <typename> struct helper;
        template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
        {
            using type = std::integer_sequence<T, pair.first[ms]...>;
        };
        using type = typename helper<std::make_index_sequence<pair.second>>::type;
    };

    template <auto... ns1, auto... ns2> struct set_union<set<ns1...>, set<ns2...>>
    {
        static constexpr auto pair = [](){
            std::array<T, sizeof...(ns1)> arr1{ ns1...};
            std::array<T, sizeof...(ns2)> arr2{ ns2...};
            std::array<T, sizeof...(ns1) + sizeof...(ns2)> arr;            
            auto const sorted_size = std::set_symmetric_difference(arr1.begin(), arr1.begin(), arr2.begin(), arr3.begin(), arr.begin())
               - arr.begin();
            return std::make_pair(arr, sorted_size); }();
        template <typename> struct helper;
        template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
        {
            using type = std::integer_sequence<T, pair.first[ms]...>;
        };
        using type = typename helper<std::make_index_sequence<pair.second>>::type;
    };



}

