#pragma once
#include <algorithm>
#include <concepts>
#include <functional>
#include <iterator>

namespace ugarit
{

namespace ranges
{
    ///\brief test, whether a sequence is strictly monotonous ascendig
    struct is_unique_fn
    {
        template<std::forward_iterator I, 
                 std::sentinel_for<I> S,
                 class Proj = std::identity,
                 std::indirect_strict_weak_order<std::projected<I, Proj>>
                 Comp = std::ranges::greater>
        constexpr bool operator()(I first, S last, Comp comp = {}, Proj proj = {}) const
        {
            return ranges::is_sorted_until(first, 
                                           last, 
                                           [&comp](auto &a, auto &b){ 
                                              return !comp(a,b); 
                                           }, 
                                           proj) == last;
        }
    
        template<std::ranges::forward_range R, 
                 class Proj = std::identity,
                 std::indirect_strict_weak_order<std::projected<std::ranges::iterator_t<R>, Proj>>
                 Comp = std::ranges::greater>
        constexpr bool operator()(R&& r, Comp comp = {}, Proj proj = {}) const
        {
            return (*this)(ranges::begin(r), ranges::end(r), std::ref(comp), std::ref(proj));
        }
    };

    ///\brief test, whether a range is strictly monotonous ascendig.
    ///
    /// The name `is_unique` has been chosen to be consistent with the unique algorithm of the Standard Library,
    /// which sorts as a side effect.
    inline constexpr is_unique_fn is_unique;
}
}

