module;

#include <concepts>
#include <cstdint>

export module ugarit:sparse;

namespace ugarit
{
    using Bases = std::uintmax_t;

    template <typename T>
    concept Module = requires(T t){

       {T{}};
       {T{0}};
       {+t} -> std::same_as<T>;
       {-t} -> std::same_as<T>;
       {t+t} -> std::same_as<T>;
       {t-t} -> std::same_as<T>;
       {t*t} -> std::same_as<T>;
       {t/t} -> std::same_as<T>;
    };

    template <typename M>
    concept BilinearForm = requires (M m, Bases a, Bases b){
        { m(a,b) } -> std::convertible_to<Bases>;
        { std::integral_constant<Bases, M::operator()(Bases{},Bases{})>{} }; // test constexpr
    };

    struct OuterMetric
    {
        constexpr static auto operator()(Bases, Bases){ return 0; };
    };

    struct OuterContext{
        using metric = OuterMetric;
    };

    template <typename T>
    concept Context = BilinearForm<typename T::metric>;

    template <typename T>
    concept MVExpr = requires (T const t, Bases b)
    {
        { get<Bases{}, OuterMetric>(t) } -> Module;
    };
}