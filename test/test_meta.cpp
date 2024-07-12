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