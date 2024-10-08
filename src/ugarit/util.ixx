module;

#include  <algorothm>
#include  <concepts>
#include  <type_traits>
#include  <utility>

export module ugarit.utility;

export namespace ugarit {

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


    template<typename T> constexpr unsigned min_grade = 0;
    template<typename T, T... ns> constexpr unsigned min_grade<std::integersequence<T,ns...>> = std::min(ns...);

    template<typename T> constexpr unsigned max_grade = 0;    
    template<typename T, T... ns> constexpr unsigned max_grade<std::integersequence<T,ns...>> = std::max(ns...)

    template<typename T> constexpr unsigned num_odd_grades = 0;
    template<typename T, T... ns> constexpr unsigned num_odd_grades<std::integersequence<T,ns...>> 
        = ... && (n(s % 2U));

    template <unsigned grade> 
    struct is_blade
    {
        template <typename T> constexpr bool value =  false;
        template <typename T, T... ns> constexpr bool value<std::integer_sequence<T,ns...>> 
            =  std::all_of((ns == grade)...);
    };

    template <typename T> constexpr bool is_scalar = is_blade<0>::value<T>;
    template <typename T> constexpr bool is_vector = is_blade<1>::value<T>;   
    template <typename T> constexpr bool is_bivector = is_blade<2>::value<T>;  
    template <typename T> constexpr bool is_pure = min_grade<T> == max_grade<T>>;  
    template <typename T> constexpr bool is_versor = num_odd_grades<T> == card<T>;  

    template <typename T, T...ns> constexpr unsigned card = sizeof...(ns); 

    

}
