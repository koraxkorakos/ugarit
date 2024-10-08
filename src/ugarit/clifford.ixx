module;

#include  <concepts>
#include  <type_traits>

export module ugarit.cliffford;

namespace ugarit {

    template <typename T, T... ns> requires std::is_arithmetic_v<T>
    struct make_integer_set;


}

// module : private

namespace ugarit {
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
}