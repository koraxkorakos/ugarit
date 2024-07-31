#pragma once
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

        using Nat = unsigned;        
        using Int = signed;        

        template <typename T>
        concept MetaFunction = requires {
            typename T::type;
        };

        using True = std::true_type;
        using False = std::false_type;

        template <bool cond> using Bool = std::bool_constant<cond>;
        template <int n> using IntT = std::integral_constant<int,n>;

        template <typename T>
        concept ConvertibleToBool = requires 
        {
            { T::value } -> std::convertible_to<bool>;
        };

        template <typename T>
        concept UnsignedIntegral = requires 
        {
            { T::value } -> std::convertible_to<Nat>;
            { std::bool_constant<(T::value >= 0)>{} } -> std::same_as<std::true_type>;
        };

        template <typename T>
        concept SignedIntegral = requires 
        {
            { T::value } -> std::convertible_to<Int>;
        };


        template <typename T> struct Quote{ using type = T; };    ///< Metafunction return type T
        template <typename T> using Return = Quote<T>;            ///< Metafunction return type T
        template <typename...> struct List{ using type = List; }; ///< Metafunction List constructor

        struct Error; ///< meta programming result in case of error, e.g. pop_front on an empty list
                      ///< 
                      ///< Intentionally left undefined.

        struct Delim; ///< used as a separator in template argument lists
        
        struct Fail{ template <typename...> using f = Error; }; ///<f HOMF which yields error upon invocation

        template <bool> struct Ifc; ///< HOMF to switch between two type parameters
        template <> struct Ifc<true>   { template <typename T, typename> using f = T;  };   
        template <> struct Ifc<false>  { template <typename, typename T> using f = T;  };      
        template <ConvertibleToBool cond> using If = Ifc<cond::value>;
        template <bool cond, typename T, typename F> using Alternativec = typename Ifc<cond>::template f<T,F>;
        template <ConvertibleToBool cond, typename T, typename F> using Alternative = Alternativec<cond::value,T,F>;

        struct Head {  template <typename T, typename...> using f = T;  };///< HOMF extract the first of a parameter list of type parameters

        template <Nat n> struct Atc; ///< HOMF to extract nth element of a parameter list of type parameters
        template <Nat n> struct Atc
        {
            template <typename, typename... TS> 
            using f = Alternativec<(sizeof...(TS) > 0), Atc<Nat{n}-Nat{1}>, Fail>::template f<TS...>;
        };

        template <> struct Atc<Nat{}> : Head{}; 
        
        template <UnsignedIntegral V> using At = Atc<V::value>;
       

        struct Listify { template <typename... TS > using f = List<TS...>;  }; ///< HOMF to store type parameters in a list

        template <typename C = Listify> struct Call 
        {
            template <typename... TS > using f = typename C::template f<TS...>;
        };

        template <Nat n, typename C = Listify> struct PopFrontc ///< HOMF returnning list with first n template parameters dropped
        {
            template <typename, typename... TS> using f = typename Alternativec<(sizeof...(TS) > 0), 
                                                                                PopFrontc<n-Nat{1},C>,
                                                                                C>::template f<TS...>; 
        };
        template <typename C> struct PopFrontc<Nat{},C> : C{};


        template <UnsignedIntegral V, typename C = Listify> using PopFront = PopFrontc<V::value, C>;


        template <typename C = Listify> using PushFront = C;

        namespace details
        {
            struct RotateStop
            {
                template <Nat, typename C, typename... TS> using f = typename C::template f<TS...>;
            };

            /// precondition list to rotate has more than one element
            struct RotateOne
            {
                template <Nat n, typename C, typename T, typename... TS> using f = 
                    typename Alternativec<  (n && sizeof...(TS)),
                                            RotateStop,
                                            RotateOne                                            
                                         >::template f<(n - Nat{1}), C, TS..., T>;
            };

            constexpr std::size_t compute_rotation(std::size_t sz, unsigned n) // negative n gets wrapped by conversion
            {
                return sz > 1U  ? n % sz  : 0U; 
            }
        } // namespace details


        template <Int n, typename C = Listify> struct Rotatec
        {
            template <typename... TS> using f = typename Alternativec<details::compute_rotation(sizeof...(TS), n), 
                                                                      details::RotateOne,
                                                                      details::RotateStop                                                                    
                                                                    >::template f<
                                                                        details::compute_rotation(sizeof...(TS), n),
                                                                        C, 
                                                                        TS...>; 
        };


        template <SignedIntegral V, typename C = Listify> using Rotate = Rotatec<V::value, C>;

#if XXX
        template <Metafunction Less> struct Equivalent
        {
            template <typename A, typename B> using type = Less::template<A,B>
        };

        struct Insert<
        {
            Min<Less>::template f<TS...>, 
        };


        template <typename Less, typename C = Listify>  struct Unique; ///< \todo

        

    }
//____________________________________________
    template<Nat n, typename C = Listify> 
    struct For{
        template <typename F, typename... TS> using f = For<n-1, C>::template apply<TS...>;
    }


    template <Nat n, typename C = Listify>
    struct Rotate
    {
        template <typename T, typename... TS> using f = Rotate<n-1, C>::template f<TS..., T>;
    };

    template <typename C>
    struct Rotate<Nat{}, C>
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
    template <Nat... ns>  
    struct bits;

    template <Nat... ns> requires { is_strictly_sorted(ns...) }
    struct bits<ns...>{};

    template <Nat... ns> requires { !is_strictly_sorted(ns...) }
    struct bits<ns...>;*/

    template <Nat n>  
    struct bits_;

    template <Nat n> requires 
    { 
        std::is_same_t<
            std::integral_constant<Nat, n>,
            std::integral_constant<Nat, (n / 2) * 2>
        > 
    }
    struct bits_<ns...>{};

    template <Nat n> requires { n % 2 = 1 }
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
    } // meta
} // ugarit

