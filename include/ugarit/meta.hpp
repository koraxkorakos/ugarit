#pragma once
#include <concepts>
#include <cstdint>


/// HOMF = Higher Ordr Metafunction
///
/// A type with a nested template <TLIST....> using f = ...;
///
/// TLIST can be a list of n to m, 0 <= n <= m, type or value parameters, a type pack allowed at the end

namespace ugarit {

    namespace meta {

        using N = std::uintmax_t;

        template <typename T>
        concept MetaFunction = requires {
            typename T::type;
        };

        template <typename T> struct Quote{ using type = T; };    ///< Metafunction return type T
        template <typename T> using Return = Quote<T>;            ///< Metafunction return type T
        template <typename...> struct List{ using type = List; }; ///< Metafunction List constructor

        struct Error; ///< meta programming result in case of error, e.g. pop_front on an empty list
                      ///< 
                      ///< Intentionally left undefined.

        
        struct Fail{ template <typename...> using f = Error; }; ///<f HOMF which yields error upon invocation

        template <bool cond> struct If; ///< HOMF to switch between two type parameters
        template <> struct If<true>   { template <typename T, typename> using f = T;  };   
        template <> struct If<false>  { template <typename, typename T> using f = T;  };      
        template <bool cond, typename T, typename F> using Ifc = typename If<cond>::template f<T,F>;

        struct Head {  template <typename T, typename...> using f = T;  };///< HOMF extract the first of a parameter list of type parameters

        template <N n> struct At; ///< HOMF to extract nth element of a parameter list of type parameters
        template <N n> struct At
        {
            template <typename, typename... TS> 
            using f = Ifc<(sizeof...(TS) > 0), At<N{n}-N{1}>, Fail>::template f<TS...>;
        };

        template <> struct At<N{}> : Head{}; 
        

        struct Listify { template <typename... TS > using f = List<TS...>;  }; ///< HOMF to store type parameters in a list

        template <typename C = Listify> struct Call 
        {
            template <typename... TS > using f = typename C::template f<TS...>;
        };

        template <N n, typename C = Listify> struct PopFront ///< HOMF returnning list with first n template parameters dropped
        {
            template <typename, typename... TS> using f = typename Ifc<(sizeof...(TS) > 0), 
                                                                       PopFront<n-N{1},C>,
                                                                       C>::template f<TS...>; 
        };

        template <typename C> struct PopFront<N{},C> : C{};


        template <typename C = Listify> using PushFront = C;


        template <typename Less, typename C = Listify>  struct Unique; ///< \todo

        

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
