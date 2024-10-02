#pragma once
#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <functional>
#include <ranges>
#include <span>
#include <type_traits>
#include <utility>


namespace ugarit {
namespace meta {

using N = std::uintmax_t;

template <N... ns> using NSequence = std::integer_sequence<N, ns...>;  ///< compile time sequence of integers
template <N n> using Iota = std::make_index_sequence<n>;               ///< create compile time sequence fro 0 to n-1

// --- traits ---
template <typename T> struct is_NSequence : std::false_type {};  ///< trait to check whether a type is an NS instance
template <N... ns> struct is_NSequence<NSequence<ns...>> : std::true_type {};  ///< specialization
template <N... ns>
using is_unique_seq = std::bool_constant<std::ranges::is_sorted(
    std::initializer_list<N>{ns...}, std::less_equal<N>{})>;  ///< query whether sequence ist
                                                              ///< strictly sorted in ascending order
template <typename T> struct is_NSet : std::false_type {};    ///< trait to check whether a type is an NS instance
                                                              ///< that is strictly sorted in ascending order
template <N... ns> struct is_NSet<NSequence<ns...>> : is_unique_seq<ns...> {};  ///< specialization

#ifndef META_CONCEPT_CHECK
template <typename T>
concept NSeq = true;
template <typename T>
concept NSet = true;
#else
template <typename T>
concept NSeq = is_NSet<T>::value;
template <typename T>
concept NSet = NSeq<T> && is_NSet<T>::value;
#endif

// --- algorithms -------------------------------------------------------------
template <NSeq> struct Sort;    ///< metafunction that returns an `NSequence` sorted
template <NSeq> struct Unique;  ///< metafunction that returns an `NSequence` sorted and removes duplicate entries

template <N... ns> struct Sort<NSequence<ns...>> {
  static constexpr N getNthElement(N i) {
    N arr[] = {ns...};
    std::ranges::sort(arr);

    return arr[i];
  }
  template <typename> struct Helper;
  template <std::size_t... indices> struct Helper<std::integer_sequence<std::size_t, indices...>> {
    using type = NSequence<getNthElement(indices)...>;
  };
  using type = Helper<Iota<sizeof...(ns)>>;
};

template <N... ns> struct Unique<NSequence<ns...>> {
  static constexpr auto data = []() {
    using namespace std;
    static N arr[] = {ns...};
    return span<unsigned const>(cbegin(arr), unique(begin(arr), end(arr)));
  }();

template <int... Indices> using type = NSequence<data[Indices]...>;
};

}  // namespace meta
#if 0
namespace homf
{

template <typename T>struct Intersection;

  template <typename C = Listify>
  struct Unique {
    template <N... ns> using apply = C::template apply<meta::NSequence<ns...>::data[Indices]...>;
  };

  template <typename C = Listify>
  struct Union {
    template <typename... Ts> using apply = typename Union::template apply_<TS...>::type;
    template <typename... Ts> struct apply_ : typename C::template appy<>::type;
    template <N... ns, typename... Ts> struct apply_<meta::NSequence<ns...>, Ts...> 
      = C::template apply<meta::NSequence<ns...>::data[Indices]...>;
  };

#endif
}  // namespace ugarit
