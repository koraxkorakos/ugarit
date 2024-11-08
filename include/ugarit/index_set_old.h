#pragma once
#include <ugarit/meta.h>
namespace ugarit
{

    namespace details
    {
        template <integral_type T, T... ns> 
        struct make_integer_set_ {
            static constexpr auto pair = [](){
                std::array<T, sizeof...(ns)> arr{ ns... };
                std::sort(arr.begin(), arr.end());
                auto const sorted_size = std::unique(arr.begin(), arr.end()) - arr.begin();
                return std::make_pair(arr, sorted_size); }();
            template <typename> struct helper;
            template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
            {
                using type = std::integer_sequence<T, pair.first[ms]...>;
            };
            using type = typename helper<std::make_index_sequence<pair.second>>::type;
        };

        template <typename, typename> struct make_integer_set_intersection_;
        template <typename T, T...ns1, T...ns2, typename>
        struct make_integer_set_intersection_<std::integer_sequence<T,ns1...>, std::integer_sequence<T,ns2...>>
        {
            static constexpr auto pair = [](){
                constexpr std::integral_sequence<T> s1 = {ns1...};
                constexpr std::integral_sequence<T> s2 = {ns2...};
                constexpr autp n = std::min(size(ns1), size...(ns2));
                std::array<T,n> arr;
                auto const sz = std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), arr.begin()) - arr.begin();
                return std::make_pair(arr, sz);                
            }();
            template <typename> struct helper;
            template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
            {
                using type = std::integer_sequence<T, pair.first[ms]...>;
            };
            using type = typename helper<std::make_index_sequence<pair.second>>::type;            
        };
    }

    template <integral_type T, T... ns> using int_set
        = typename details::make_integer_set_<T, ns...>::type;

    template <integral_type T, T... ns> using int_seq
        = std::integer_sequence<T, ns...>::type;

    template <std::size_t... ns> using idx_set
        = int_set<std::size_t, ns...>;

    template <std::size_t... ns> using idx_seq
        = std::index_sequence<ns...>;

    namespace details{
        template <typename... T> struct set_union_;
        template <typename T, T...ns> struct set_union_<int_set<T,ns...>> { 
            using type = int_set<T,ns...>; 
        };
        template <typename T, T... ns1, T... ns2> 
        struct set_union_<int_seq<T, ns1...>, int_seq<T, ns2...>> :
            make_integer_set<T, ns1..., ns2...>{};
        template <typename T1, typename T2, typename...Ts> 
        struct set_union_<int_seq<T, ns1...>, int_seq<T, ns2...>> :
            set_union_<typename set_union_<T1, T2>::type, Ts...>{};

        template <typename... T> struct set_intersection;
        template <typename T, T...ns> struct set_intersection_<int_set<T,ns...>> { 
            using type = int_set<T,ns...>; 
        };
        template <typename T, T... ns1, T... ns2> 
        struct set_intersection<int_seq<T, ns1...>, int_seq<T, ns2...>> :
            make_set_intersection<T, ns1..., ns2...>{};
        template <typename T1, typename T2, typename...Ts> 
        struct set_intersection<int_seq<T, ns1...>, int_seq<T, ns2...>> :
            set_intersection<typename set_intersection<T1, T2>::type, Ts...>{};            
    }

    template <typename... Ts> using set_union = typename details::set_union_<Ts...>::type;
    template <typename... Ts> using set_intersection = typename details::set_intersection_<Ts...>::type;

}
