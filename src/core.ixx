module;

#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <iterator>
#include <type_traits>
#include <utility>

export module ugarit:core;

namespace ugarit {

    export using Bases = ::std::uintmax_t;    

    ///\brief meta function constructing integer sets from a variadic list of integers parameters
    template <typename T, T... ns> requires std::is_arithmetic_v<T>
    struct make_integer_set {
        static constexpr auto pair = [](){
            std::array<T, sizeof...(ns)> arr{ ns... };
            std::sort(begin(arr), end(arr));
            auto const sorted_size = std::unique(begin(arr), end(arr)) - begin(arr);
            return std::make_pair(arr, sorted_size); }();
        template <typename> struct helper;
        template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
        {
            using type = std::integer_sequence<T, pair.first[ms]...>;
        };
        using type = typename helper<std::make_index_sequence<pair.second>>::type;
    };

    
    export template <typename T, T... ns> using integer_set 
        = typename make_integer_set<T, ns...>::type; ///< setup integer set holding sorted unique numbers passed

    export template <std::size_t ... ns> using index_set 
        = integer_set<std::size_t, ns...>; ///< setup integer set holding sorted unique numbers passed

    export template <typename T, T... ns> using integer_seq 
        = std::integer_sequence<T, ns...>; ///< short alias for std integer sequence
    
    export template <std::size_t... ns> using index_seq 
        = std::index_sequence<ns...>; ///< short alias for std index sequence

    ///\return -1 if `value` is not containes within sequence, otherwise
    /// it return its position
    template <typename T, typename T::value_type> constexpr int pos;
    template <typename T, typename T::value_type value, typename T::value_type... ns> 
        constexpr int pos<std::integer_sequence<T,ns...>,value> =  
        [](std::initializer_list<typename T::value_type> s, typename T::value_type  v)
        {
            auto const pos = std::ranges::find(s) - s.begin();
            return  pos > s.size() ? -1 : pos;
        }({ns...}, value);
 
    template <typename T, typename T::value_type v> constexpr bool contains = pos<T,v> >= 0;


/*
    template <typename T, T... ns> 
    using BasesSet = integer_set<Bases, ns...>;

    template <typename T> constexpr bool is_integer_set = false; ///< helper predicate to determine, whether type is a integer set
    template <typename N, N... ns> 
      constexpr bool is_integer_set<std::integer_sequence<N, ns...>> ///< specializations for integer_sequences
        = std::is_sorted<std::less_equal<N>>({ns...});

    template <typename T> constexpr bool is_empty_set = false; ///< helper predicate to determine, whether type is a integer set
    template <typename N, N... ns> 
      constexpr bool is_empty_set<std::integer_sequence<N, ns...>> ///< specializations for integer_sequences
        = !sizeof...(ns);

    template<typename T> concept IntSet = is_integer_set<T>; ///< unique sorted compile time integer sequence
    template<typename T> concept Arithmetic = std::is_arithmetic_v<T>; ///< unique sorted compile time integer sequence

    template <typename T> constexpr auto cardinality = 0U:
    template <typename T, T...ns> constexpr auto cardinality<std::integer_sequence<T, ns...>> = sizeof...(ns):


    ///< mixin
    template <typename D, IntSet b> 
    struct MV_mixin{
    private:       
       D & derived() const{ return static_cast<D &>(); }
       D const & derived() const &{ return static_cast<D const &>(); }
       D && derived() const &&{ return static_cast<D &&>(); }
       friend class D;
    };

    template <Arithmetic T> 
    class Scalar : public MV_mixin<Scalar<Arithmetic>, BasesSet<>> {
    public:
        Scalar(T const &t, std::enable_if_t<is_empty_set_v-<b>,bool> = nullptr) : t{t}{} ///< conversion constructor
        constexpr static operator[](Sig s){ return s ? t : T{}; }
    private:       
      T t;
    };

    template <Arithmetic T = double, BasesSet  b, typename Container = std::array<T, b>>  class MV;

    template <Arithmetic T, Bases... s, typename Container> 
    class MV<Bases<s...>, std::array<T, sizeof...(s)>> : public MV_mixin<Scalar<Arithmetic>, BasesSet<>> {
    public:
        MV(T const &t, std::enable_if_t<is_empty_set_v-<b>,bool> = nullptr) : t{t}{} ///< conversion constructor
        constexpr static operator[](Sig s){ return s ? t : T{}; }

        // grz---
    private:       
      std::T t;
    };    
   

    template <typename D> 
    struct MV {
    private:
       D & derived() const{ return static_cast<D &>(); }
       D const & derived() const &{ return static_cast<D const &>(); }
       D && derived() const &&{ return static_cast<D &&>(); }
       friend class D;
    };
*/

}