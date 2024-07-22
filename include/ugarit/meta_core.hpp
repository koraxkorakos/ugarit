#pragma once
namespace ugarit
{
    template <typename T>
    concept MetaFunction = requires {
        typename T::type;
    };


    struct Identity
    {
        template <typename T> using f = T;
    };

    template <unsigned n> struct Select;

    template <> struct Select<0U>
    {
        template <typename T, typename... TS> using f = T;
    };

    template <unsigned n> struct Select
    {
        template <typename T, typename... TS> using f 
            = Select<n - 1U>::template f<TS...>;
    };

    template <bool c, typename T, typename F> 
    using Condition = typename Select<!c>::template f<T, F>;


    // constant, evaluates to itself
    template <typename...> struct List
    {
        template <typename...> using f = List;
    };
    
    struct Listify {
        template <typename... TS> using f = typename template List<TS...>;
    };


    template <MetaFunction F = Identity, typename C = Listify>
    struct Transform {
        template <typename... TS> using f = typename C::template f<F<TS>>...;
    };


    struct Unique {
        template <typename... TS> using f =
            Merge::template f<Odd::template f<TS...>, Even::template f<TS...>>
            typename Conditional<sizeof...(TS), A, B>
                ::template f<F<TS>>...;
    };


}