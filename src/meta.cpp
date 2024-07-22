export module ugarit;

#include <concepts>
#include <type_traits>
#include <cstdint>

export{
    namespace ugarit {
        using bits = std::uintmax_t;

        template <typename T>
        concept Arithmetic = std::is_arithmetic_v<T>;

        template <typename T>
        concept BladeSig = requires(T t) {
            { T::sig } -> std::same_as<bits>;
        };

        template <typename T> struct bb;

        template <Arithmetic T> struct bb<T> : std::integral_constant<bits, bits{}>{};
    }

}