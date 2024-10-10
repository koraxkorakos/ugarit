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

    template <bool> struct cond{
        template <typename, typename F> using f = F;
    };

    template <> struct cond<true>{
        template <typename T, typename F> using f = T;
    };


    export using Bases = ::std::uintmax_t;    

    export template <typename T> concept integral_type = std::is_integral_v<T>;

    ///\brief meta function constructing integer sets from a variadic list of integers parameters
    export template <integral_type T, T... ns> requires std::is_arithmetic_v<T>
    struct make_integer_set {
        static constexpr auto pair = [](){
            std::array<T, sizeof...(ns)> arr{ ns... };
            std::sort(arr.begin(), arr.end());
            auto const sorted_size = std::unique(arr.begin(), arr.end()) - arr.begin();
            return std::make_pair(arr, sorted_size); }();
        template <typename> struct helper;
        template <std::size_t... ms> struct helper<std::index_sequence<ms...>>
        {
            using type = std::integer_sequence<T, pair.first[ms]...>;
        };
        using type = typename helper<std::make_index_sequence<pair.second>>::type;
    };
    
    export template <integral_type T, T... ns> using integer_set 
        = typename make_integer_set<T, ns...>::type; ///< setup integer set holding sorted unique numbers passed

    export template <std::size_t ... ns> using index_set 
        = integer_set<std::size_t, ns...>; ///< setup integer set holding sorted unique numbers passed

    export template <integral_type T, T... ns> using integer_seq 
        = std::integer_sequence<T, ns...>; ///< short alias for std integer sequence
    
    export template <std::size_t... ns> using index_seq 
        = std::index_sequence<ns...>; ///< short alias for std index sequence

    ///\brief query whether value is contained in sequence `{ns...}`
    ///\tparam T an integer type allowed for std::integer_sequence
    template <integral_type T, T... ns>
    consteval auto containes_(std::integer_sequence<T,ns...>,T value)  { 
        return std::ranges::contains({ns...}, value); 
    };

    ///\brief query entry at index
    ///\return position of first occurance of `value` within `{ns...}`
    ///\retval -1 if `value` is not contained within sequence, otherwise   
    template <integral_type T, T... ns>
    consteval auto at_(std::integer_sequence<T,ns...>,std::size_t pos) -> std::size_t { 
        static_assert(pos < sizeof...(ns));
        auto const ini_list = {ns...};
        return ini_list[pos];
    };  

    ///\brief query index of entry, whose value ie `value`
    ///\return position of first occurance of `value` within `{ns...}`
    ///\retval -1 if `value` is not contained within sequence, otherwise   
    template <integral_type T, T... ns>
    consteval auto pos_(std::integer_sequence<T,ns...>,T value) -> std::ptrdiff_t { 
        auto const seq = {ns...};
        auto const pos = std::ranges::find(seq, value) - begin(seq); 
        return pos ==  sizeof...(ns) ? -1 : pos;
    };

    template <typename T>
    consteval std::ptrdiff_t get_pos(std::size_t n, std::initializer_list<T> lst) {
        auto const pos = std::ranges::find(lst, n) - lst.begin();
        return pos == lst.size() ? -1 : pos;
    };

    template <typename T>
    consteval std::ptrdiff_t get_at(std::size_t n, std::initializer_list<T> lst) {
        return *(lst.begin()+n);
    };    

    export template <typename T, typename T::value_type v> constexpr std::ptrdiff_t pos = -1; 
    export template <typename T, typename T::value_type v, T... ns> 
        constexpr std::ptrdiff_t pos<std::integer_sequence<T, ns...>, v> = get_pos<T>(v, ns...); 

    export template <typename T, typename T::value_type v> constexpr bool containes = pos<T,v> >= 0; 

    export template <typename T, std::size_t n> constexpr nullptr_t at; // spoil general
    export template <typename T, std::size_t n, T...ns> constexpr 
        auto at<std::integer_sequence<T,ns...>, n> = get_at(n, {ns...});


///\todo vectorized at, pos, contains (=intrsection)

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