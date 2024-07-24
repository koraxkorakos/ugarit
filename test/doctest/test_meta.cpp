#include <doctest/doctest.h>
//ugarit:meta;
#include <type_traits>

#include <ugarit/meta.hpp>
// check header guard
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

TEST_CASE("test meta::Quote")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Quote<int>::type, int>));    
}

TEST_CASE("test meta::Return")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Return<int>::type, meta::Return<int>::type>));    
}


TEST_CASE("test meta::If")
{
    namespace meta = ugarit::meta;
}

TEST_CASE("test meta::Ifc")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Ifc<true, int, long>, int>));
    CHECK((std::is_same_v<meta::Ifc<false, int, long>, long>));
}

TEST_CASE("test meta::Fail")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Fail::f<>, meta::Error>));
    CHECK((std::is_same_v<meta::Fail::f<int>, meta::Error>));
    CHECK((std::is_same_v<meta::Fail::f<long, int>, meta::Error>));
}

TEST_CASE("test meta::At")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::At<0>::f<int>, int>));
    CHECK((std::is_same_v<meta::At<0>::f<int, long>, int>));
    CHECK((std::is_same_v<meta::At<1>::f<int, long>, long>));
    CHECK((std::is_same_v<meta::At<2>::f<int, long, bool>, bool>));
}

TEST_CASE("test meta::List")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::List<>, meta::List<>::type>));
    CHECK((std::is_same_v<meta::List<char>, meta::List<char>::type>));
    CHECK((std::is_same_v<meta::List<char,int>, meta::List<char,int>::type>));

    CHECK_FALSE((std::is_same_v<meta::List<char,int>, meta::List<int,char>::type>));
    CHECK_FALSE((std::is_same_v<meta::List<char>, meta::List<>::type>));
}

TEST_CASE("test meta::Listify")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::At<0>::f<int>, int>));
    CHECK((std::is_same_v<meta::At<0>::f<int, long>, int>));
    CHECK((std::is_same_v<meta::At<1>::f<int, long>, long>));
    CHECK((std::is_same_v<meta::At<2>::f<int, long, bool>, bool>));
}


namespace 
{
    template <typename... TS> struct WrapList;

    struct Wrap
    {
        template <typename... TS> using f = WrapList<TS...>;
    };
}

TEST_CASE("test meta::PopFront")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::PopFront<0>::f<>, meta::List<>>));
    CHECK((std::is_same_v<meta::PopFront<0>::f<int>, meta::List<int>>));
    CHECK((std::is_same_v<meta::PopFront<0>::f<int, char>, meta::List<int, char>>));

    CHECK((std::is_same_v<meta::PopFront<1>::f<int>, meta::List<>>));
    CHECK((std::is_same_v<meta::PopFront<1>::f<int, char>, meta::List<char>>));

    CHECK((std::is_same_v<meta::PopFront<2>::f<int,char>, meta::List<>>));
    CHECK((std::is_same_v<meta::PopFront<2>::f<int, char,bool>, meta::List<bool>>));


    CHECK((std::is_same_v<meta::PopFront<0,Wrap>::f<>, WrapList<>>));
    CHECK((std::is_same_v<meta::PopFront<0,Wrap>::f<int>, WrapList<int>>));
    CHECK((std::is_same_v<meta::PopFront<0,Wrap>::f<int, char>, WrapList<int, char>>));

    CHECK((std::is_same_v<meta::PopFront<1,Wrap>::f<int>, WrapList<>>));
    CHECK((std::is_same_v<meta::PopFront<1,Wrap>::f<int, char>, WrapList<char>>));

    CHECK((std::is_same_v<meta::PopFront<2,Wrap>::f<int,char>, WrapList<>>));
    CHECK((std::is_same_v<meta::PopFront<2,Wrap>::f<int, char,bool>, WrapList<bool>>));
}

TEST_CASE("test meta::PushFront")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::PushFront<>, meta::Listify>));
    CHECK((std::is_same_v<meta::PushFront<Wrap>, WrapList<>>));
}


