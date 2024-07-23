#include <gtest/gtest.h>
#include "../include/ugarit/meta.hpp"

namespace
{
    struct MF1
    {
        using type = void;
    };

    struct MF2
    {
        struct type{};
    };

    struct NoMF{};

    struct HOMF1 
    {
        template <typename...> using f = void;
    };

    struct HOMF2
    {
        template <typename...> class f{};
    };

    struct HOMF3
    {
        template <typename...> class f{};        
        template <typename T, typename... TS> class f<T,TS...>{};
    };

    struct NoHOMF1{};
    struct NoHOMF2{
        using f = void;
    };

    TEST(meta, mf_concept){
        ASSERT_TRUE(ugarit::MetaFunction<MF1>);        
        ASSERT_TRUE(ugarit::MetaFunction<MF2>);        
        ASSERT_FALSE(ugarit::MetaFunction<NoMF>);            
        ASSERT_FALSE(ugarit::MetaFunction<void>);                    
    }

    TEST(meta, homf_concept){
        ASSERT_TRUE(ugarit::HigherOrderMetaFunction<HOMF1>);        
        ASSERT_TRUE(ugarit::HigherOrderMetaFunction<HOMF2>);        
        ASSERT_TRUE(ugarit::HigherOrderMetaFunction<HOMF3>);            
        ASSERT_FALSE(ugarit::HigherOrderMetaFunction<NoHOMF1>);            
        ASSERT_FALSE(ugarit::HigherOrderMetaFunction<NoHOMF2>);                    
        ASSERT_FALSE(ugarit::HigherOrderMetaFunction<void>);            
    }


}
