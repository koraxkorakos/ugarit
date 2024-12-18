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
    template <integral_type T, T... ns> requires std::is_arithmetic_v<T>
    struct integer_set_ {
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
        = typename integer_set_<T, ns...>::type; ///< setup integer set holding sorted unique numbers passed

    export template <std::size_t ... ns> using index_set 
        = integer_set<std::size_t, ns...>; ///< setup integer set holding sorted unique numbers passed

    export template <integral_type T, T... ns> using integer_seq 
        = std::integer_sequence<T, ns...>; ///< short alias for std integer sequence
    
    export template <std::size_t... ns> using index_seq 
        = std::index_sequence<ns...>; ///< short alias for std index sequence

    export template <typename T> struct make_unique_sorted_;
    export template <typename T, T... ns> struct make_unique_sorted_<std::integer_sequence<T, ns...>> 
    {
        using type = integer_seq<T, ns...>;
    }; 

    ///\brief create a set from a sequence by sorting and removing duplicates
    template <typename T> using to_set = typename make_unique_sorted_<T>::type;

    /// intentionally left undefined (unly specializations are defined)
    export template <typename T, std::size_t> typename T::value_type at;
    ///\brief retrive integer in integersequence by position
    ///\return integer value ins sequenceat a given position
    ///\pre position must be a valid position, i.e. it must not index outside of the integer sequernce
    export template <typename T, T... ns, std::size_t n> constexpr typename T::value_type at<std::integer_sequence<T, ns...>, n>
       = []() -> T{
        std::initializer_list<T> const lst = {ns...};
        static_assert(n < sizeof...(ns));
        return *(lst.begin() + n);
    }();

    /// intentionally left undefined (unly specializations are defined)
    export template <typename T, typename T::value_type v> std::size_t pos;
    ///\brief locate integer in integersequence
    ///\return position of the first occurance of `v` in integer sequence `T` 
    ///\retval -1 if element is not found
    export template <typename T, T ...ns, T v> constexpr std::size_t pos<std::integer_sequence<T, ns...>, v> 
        = []() -> std::ptrdiff_t {
        std::initializer_list<T> const lst = {ns...};
        auto const pos = std::ranges::find(lst, v) - lst.begin();
        return pos == lst.size() ? -1 : pos;
    }();

    /// intentionally left undefined (unly specializations are defined)
    export template <typename T, typename T::value_type v> bool contains;    
    ///\brief test set or sequnce inclusion given an inter sequencence and an integer vale
    ///\retval true if element v is found within the integer sequence
    ///\retval false otherwise
    export template <typename T, T ...ns, T v> constexpr bool contains<std::integer_sequence<T, ns...>, v> 
        = std::ranges::contains({ns...}, v);

    template <typename U, typename V> struct concat_;
    template <typename T, T... ns1, T... ns2> struct concat_<std::integer_sequence<T, ns1...>, std::integer_sequence<T, ns2...>> :
       std::integer_sequence<T,ns1..., ns2...>{};

    export template <typename U, typename V> using concat = typename concat_<U,V>::type;
    export template <typename U, typename V> using setunion = to_set<concat<U,V>>;

    

///\todo vectorized at, pos, contains (=intersection)

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