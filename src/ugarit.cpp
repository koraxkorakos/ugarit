module;
#include <concepts>
#include <cstdint>
#include <type_traits>

export module ugarit;

export{
    namespace ugarit {
    using bits = std::uintmax_t;

    template <typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;

    template <typename T>
    concept bladesig = requires(T t) {
        { T::sig } -> std::same_as<bits>;
    };

    template <typename T> struct bb;

    template <Arithmetic T> struct bb<T> : std::integral_constant<bits, bits{}>{};

    }
}
