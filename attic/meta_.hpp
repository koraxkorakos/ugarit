#pragma once
#include <concepts>
#include <cstdint>

namespace ugarit {

    namespace meta {

        using N = std::uintmax_t;

        template <typename T>
        concept MetaFunction = requires {
            typename T::type;
        };

        template <N n>
        struct Select  {
            template <typename T, typename... TS> using f = typename Select<n-1>::template f<TS...>;
        };

        template <>
        struct Select<N{}>  {
            template <typename T, typename...> using f = T;
        };

        template <bool b> using If = Select<!b>;

        template <typename...> struct list;

        struct Listify
        {
            template<typename...TS> using f = list<TS...>;
        };

        template <N n, typename C = Listify>
        struct PopFront  {
            template <typename, typename... TS> using f = typename PopFront<n-1>::template f<TS...>;
        };

        namespace details
        {
            template <typename... TS> using HeadOrVoid = Ifc<sizeof...(TS), Head, void> {
                template <typename T, typename, typename... TS> using f = C<T, TS...>;
            };
        }

        template <typename C>
        struct Even  {
            template <typename... TS> using f = Ifc<size...(TS), 
                                                    Popfront<Odd<C>>,
                                                    C>::template f<TS...>;
        };

        namespace details{
            template <typename C>    
            struct OddLen2plus  {
                template <typename T, typename, typename... TS> using f = Even<PushFront<T,C>>::template f<TS...>;                
            };
        }

        template <typename C>
        struct Odd  {
            template <typename T, typename, typename... TS> using f = Ifc<(size...(TS) > 1), 
                                                                          details::OddLen2plus<C>,
                                                                          Even<C>::template f<TS...>;
        };


        template <typename C>
        struct PopFront<N{}, C>  {
            template <typename... TS> using f = typename C::template f<TS...>;
        };

    }
#if 0
    template<N n, typename C = Listify> 
    struct For{
        template <typename F, typename... TS> using f = For<n-1, C>::template apply<TS...>;
    }


    template <N n, typename C = Listify>
    struct Rotate
    {
        template <typename T, typename... TS> using f = Rotate<n-1, C>::template f<TS..., T>;
    };

    template <typename C>
    struct Rotate<N{}, C>
    {
        template <typename... TS> using f = C::template f<TS...>;
    };

    template <typename C>
    struct Reverse  {
    template <typename T, typename... TS> using f = Reverse<C>::template apply<TS..., T>;

    // concepts

    template <MetaFunction F, typename C = Listify>
    struct Find {
        template <typename... TS> using f 
            = typename Select<sizeof...(TS)>::template f<
                C::template f<>>,
                C::template f<>>,
    };

    template <unsigned n, typename C> struct FindHelper;
    template <> struct FindHelper<0>{ template <typename... TS> using f = Apply<C>::typename template f<>; }
    template <> struct FindHelper<1>{ 
        template <typename T, typename... TS> 
        using f = Apply<C>::typename template f<>; }
    };

    class std::conditional<sizeof...(TS), F0, FN>::template f<>


    constexpr bool is_strictly_sorted()
    {
        return true;
    }

    constexpr bool is_strictly_sorted(N)
    {
        return true;
    }

    constexpr bool is_strictly_sorted(N n1, N n2)
    {
        return n1 < n2;
    }

    constexpr bool is_strictly_sorted(N n1, N n2, N ns...)
    {
        return n1 < n2 && is_strictly_sorted(n2, ns);
    }
  
  /*
    template <N... ns>  
    struct bits;

    template <N... ns> requires { is_strictly_sorted(ns...) }
    struct bits<ns...>{};

    template <N... ns> requires { !is_strictly_sorted(ns...) }
    struct bits<ns...>;*/

    template <N n>  
    struct bits_;

    template <N n> requires 
    { 
        std::is_same_t<
            std::integral_constant<N, n>,
            std::integral_constant<N, (n / 2) * 2>
        > 
    }
    struct bits_<ns...>{};

    template <N n> requires { n % 2 = 1 }
    struct bits_<ns...>;

    template <typename T, typename... TS>
    concept HigherOrderMetaFunction = requires(T) {
        typename T::template f<TS...>;
    };


    template <typename T> 
    concept Continuation = HigherOrderMetaFunction<T>;

    // algorithms

    // branch among a number of alternatives
    template <unsigned, Continuation C = listify> struct select;
    template <unsigned n, Continuation C = listify> struct select{
         template <typename T, typename... TS> using f = select<n-1>::template f<TS...>; };
    template <Continuation C> struct select<0U,C>{ template <typename T, typename...> using f = C::template f<T>; };
    
    // branch
    template <bool c, typename Yes, typename No> using cond = select<unsigned(c)>::template f<Yes, No>;

    // constant
    template <typename T, Continuation C = listify> 
    struct lift {
        template <typename...> using f = C:: template f<T>; 
    };

    // constant
    template <unsigned... ns> struct nlist;

    struct listify {
        template <typename... TS> using f = list<TS...>;      
    };

    template <Continuation C = listify>
    struct call {
        template <typename... TS> using f = C::template f<TS...>;      
    };

    template <Continuation C = listify>
    struct call {
        template <typename... TS> using f = C::template f<TS...>;      
    };    

    template <HigherOrderMetaFunction TF, Continuation C = listify>
    struct transform {
        template <typename... TS> using f = C::template f<TF::template f<TS>...>;      
    };

    template <HigherOrderMetaFunction TF, Continuation C = listify>
    struct find {
        template <typename... TS> using f = C::template f<TF::template f<TS>...>;      
    };

#endif

}
