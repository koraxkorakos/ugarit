#pragma once
#include <type_traits>
#include <cstdint>
#include <functional>
#include <ranges>
#include <algorithm>
#include "algorithm.hpp"


namespace ugarit
{
namespace meta
{

    using N = std::uintmax_t;
    template <N... ns> using NSeq = std::integer_sequence<N,ns...>;

    template <typename T> struct NSet; ///< intentially not defined

    template <N... ns> requires(ranges::is_unique({ns...}))
    struct NSet<NSeq<ns...>>
    {
        using type = NSet;
    };

    template <template <N...> class T, N... ns>
    concept CNSet = std::is_same_v<T<>, NSeq<>> && is_unique({ns...});

    template <N... ns> requires(is_unique({ns...}))
    using UNSet = NSeq<ns...>;

    UNSet<3,4,5> y;

    template <typename> struct Unique; 
    template <nset T> struct Unique<T> = std::type_identity<>{};

    template <N... ns> struct Unique<NSequence<ns...>> {
  static constexpr auto data = []() {
    using namespace std;
    static N arr[] = {ns...};
    return span<unsigned const>(cbegin(arr), unique(begin(arr), end(arr)));
  }();



    struct set_union;
    struct set_intersection;
    struct set_symetric_difference;
    struct set_difference;
    

} // meta
} // ugarit