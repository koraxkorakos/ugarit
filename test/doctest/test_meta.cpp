#include <doctest/doctest.h>
//ugarit:meta;
#include <ugarit/meta.hpp>

TEST_CASE("ugarit_meta, MetaFunction")
{
    struct F1{};
    struct T1 { using type = void;  };
    struct T2 { struct type{};  };

    namespace meta = ugarit::meta;

    CHECK(false == meta::MetaFunction<void>);
    CHECK(false == meta::MetaFunction<int>);
    CHECK(false == meta::MetaFunction<F1>);
    CHECK(true == meta::MetaFunction<T1>);
    CHECK(true == meta::MetaFunction<T2>);    
}

/*
namespace{
    using ugarit::N;

    template <ugarit::N... ns>
    bool choose_bits(int, ugarit::bits<ns...>={}){ return false; }
    int choose_bits(...);
}

TEST_CASE("ugarit_meta, bits")
{
    ASSERT_FALSE(ugarit::bits<>);
    ASSERT_FALSE(ugarit::bits<3>);
    ASSERT_FALSE(ugarit::bits<3>);
    ASSERT_FALSE(ugarit::HigherOrderMetaFunction<F1>);
};
*/
