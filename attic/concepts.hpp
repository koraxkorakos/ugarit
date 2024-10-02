#pragma once
#include <concepts>
#include <type_traits>
#include <utility>

namespace ugarit {

    template <typename T> 
    concept Arithmetic = std::is_arithmetic_v<T>;



    template <typename E>
    concept Metric = requires(E e) {    
        { std::hash<T>{}(a) } -> std::convertible_to<std::size_t>;
        { bb(lhs,rhs) -> std::convertible_to<BB>;
        { dot(lhs,rhs) -> Arithmetic }
    };


    template <typename E>
    concept MV = requires(E v, Metric m, BB b) {    
        { v.bbl(m) -> std::convertible_to<BBLIST>;
        { v(bb,m) -> Arithmetic }
        { v(bb) -> Arithmetic }    // default metric
    };


}