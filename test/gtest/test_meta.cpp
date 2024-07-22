#include <gtest/gtest.h>
#include <ugarit/meta.hpp>

TEST(ugarit_meta, MetaFunction)
{
    struct F1{};
    struct T1 { using type = void;  };
    struct T2 { struct type{};  };

    ASSERT_FALSE(ugarit::MetaFunction<void>);
    ASSERT_FALSE(ugarit::MetaFunction<int>);
    ASSERT_FALSE(ugarit::MetaFunction<F1>);
    ASSERT_TRUE(ugarit::MetaFunction<T1>);
    ASSERT_TRUE(ugarit::MetaFunction<T2>);
    
}

namespace{
    using ugarit::N;

    template <ugarit::N... ns>
    bool choose_bits(int, ugarit::bits<ns...>={}){ return false; }
    int choose_bits(...);
}

TEST(ugarit_meta, bits)
{
    ASSERT_FALSE(ugarit::bits<>);
    ASSERT_FALSE(ugarit::bits<3>);
    ASSERT_FALSE(ugarit::bits<3>);
    ASSERT_FALSE(ugarit::HigherOrderMetaFunction<F1>);
};

template <N... n> requires (is_strictly_sorted(n...))
struct bits{};


/*
namespace
{
    struct F1 {};
    struct T1 { template <typename T> using f = void; };
    struct T2 { template <typename T> struct f{}; };
    struct T3 { template <typename...> using f = void; };
    struct T4 { template <typename...> struct f{}; };

}

TEST(ugarit_meta, HigherOrderMetaFunction)
{
    ASSERT_FALSE(ugarit::HigherOrderMetaFunction<void>);
    ASSERT_FALSE(ugarit::HigherOrderMetaFunction<int>);
    ASSERT_FALSE(ugarit::HigherOrderMetaFunction<F1>);
    ASSERT_TRUE(ugarit::HigherOrderMetaFunction<T1,int>);
    ASSERT_TRUE(ugarit::HigherOrderMetaFunction<T2,int>);    
    ASSERT_TRUE(ugarit::HigherOrderMetaFunction<T2>);    
    ASSERT_TRUE(ugarit::HigherOrderMetaFunction<T2>);   
}
*/