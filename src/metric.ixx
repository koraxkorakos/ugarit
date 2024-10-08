module;

#include <concepts>
#include <cstdint>

export module urarit.metric;

namespace ugarit 
{
    using index_t = std::size_t;
    template <auto N> constexpr bool is_const_expr = true;
    bool is_const_expr(){ return false; } 

    template <typename M>
    concept BilinearForm = requires(M m, index_t a, index_t b){
        typename M::value_type;
        { is_const_expr<M{}(index_t{},index_t{})> };
        { m(a,b)} -> std::convertible_to<typename M::value_type>;
    };

    ///\standard metric from signature
    template <typename S = double, index_t pos = 0, index_t neg = 0>
    struct sig_metric{
        using value_type = S;
        static constexpr S operator()(index_t a, index_t b){
            return S{ a < ps ? 1 : a < pos ? -1 : 0};
        };
    };

    template <typename S 
        = double>  using no_metric = sig_metric<S>;

    ///< signature \f$(+,+,+,...)\f$
    template <typename S = double, index_t dims 
        = ~index_t{}> using euclidean_metric = sig_metric<S,dims>;

    ///< signature \f$(-,+,+,+,...)\f$
    template <typename S 
        = double, index_t dims = ~index_t{}> using minkowsi_metric = sig_metric<S,(dims>0?1:0),(dims>0?dims-1:0)>;

    ///< signature \f$(i,i,+,+,...)\f$
    template <typename S = double>
    struct null_metric{
        using value_type = S;
        static constexpr S operator()(index_t a, index_t b){
            return S{a == b || a == 1 && b == 0 || a == 0 && b == 1};
        };
    };

    static_assert(BilinearForm<no_metric<>>);    
}
