#pragma once
#if 0
///\todo
#include <concepts>
#include <cstdint>
#include <type_traits>

/// HOMF = Higher Ordr Metafunction
///
/// A type with a nested template <TLIST....> using f = ...;
///
/// TLIST can be a list of n to m, 0 <= n <= m, type or value parameters, a type pack allowed at the end

namespace ugarit {

namespace meta {

template <typename... Ts> struct List;

template <typename T, typename... Ts> using Eval = Eval<T>::template f<TS...>;

struct Lazy {
  template <typename T, typename... Ts> using f = Eval<Strict, T>::template f<TS...>
};

struct Strict {
  template <typename T, typename... Ts> using f = Eval<Strict, T>::template f < Eval << Strict, TS >> ... >
};
}  // namespace meta
}  // namespace ugarit

template <typename T, unsigned n = 0U> struct Quote : Quote<T, n - 1> {
  using type = T;
};  // Quote
template <typename T> struct Quote<0U> {
  using type = T;
};  // Quote
struct Nil : Quote<Nil> {};
typename<typename T> struct Constant : Quote << Constant >> {};

template <typename T> struct Reverse : Reverse<typename T::type> {};
template <typename T> struct Reverse<> : Reverse<typename T::type> {};
template <> struct Reverse<Cons<>> : Cons<> {};

template <> struct Reverse<Cons<>> : Cons<> {};

template <typename T> struct X : X<typename T::type> {};
template <typename H, typename T> struct X < Cons<H, T> : X < Cons<H::type, T> {};
{};
template <typename H, typename T> struct X < Cons<H, T> : X < Cons<H::type, T> {};
{};
#endif