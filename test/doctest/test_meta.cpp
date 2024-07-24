#include <doctest/doctest.h>
//ugarit:meta;
#include <iostream>
#include <type_traits>

#include <ugarit/meta.hpp>
// check header guard
#include <ugarit/meta.hpp>
#include <testutils/demangle.hpp>

using testing::demangle;
using testing::demangle_t;

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


TEST_CASE("test meta::Ifc")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Ifc<true>::template f<int, long>, int>));
    CHECK((std::is_same_v<meta::Ifc<false>::template f<int, long>, long>));
}

TEST_CASE("test meta::Alternativec")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Alternativec<true, int, long>, int>));
    CHECK((std::is_same_v<meta::Alternativec<false,int, long>, long>));
}


TEST_CASE("test meta::If")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::If<meta::True>::f<int, long>, meta::Ifc<true>::f<int, long>>));
    CHECK((std::is_same_v<meta::If<meta::False>::f<int, long>, meta::Ifc<false>::f<int, long>>));
}

TEST_CASE("test meta::Alternative")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Alternative<meta::True,int, long>, int>));
    CHECK((std::is_same_v<meta::Alternative<meta::False,int, long>, long>));
}


TEST_CASE("test meta::Fail")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Fail::f<>, meta::Error>));
    CHECK((std::is_same_v<meta::Fail::f<int>, meta::Error>));
    CHECK((std::is_same_v<meta::Fail::f<long, int>, meta::Error>));
}

TEST_CASE("test meta::Atc")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Atc<0>::f<int>, int>));
    CHECK((std::is_same_v<meta::Atc<0>::f<int, long>, int>));
    CHECK((std::is_same_v<meta::Atc<1>::f<int, long>, long>));
    CHECK((std::is_same_v<meta::Atc<2>::f<int, long, bool>, bool>));
}

namespace 
{
    template <unsigned n> using UC = std::integral_constant<unsigned, n>;
    template <long n> using LC = std::integral_constant<long, n>;
}

TEST_CASE("test meta::Atc")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::At<UC<0U>>::f<int>, int>));
    CHECK((std::is_same_v<meta::At<LC<0U>>::f<int>, int>));
    CHECK((std::is_same_v<meta::At<UC<1U>>::f<int, long>, long>));
    CHECK((std::is_same_v<meta::At<LC<2U>>::f<int, long, bool>, bool>));
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

    CHECK((std::is_same_v<meta::Listify::f<>, meta::List<>>));
    CHECK((std::is_same_v<meta::Listify::f<int>, meta::List<int>>));
    CHECK((std::is_same_v<meta::Listify::f<int, long>, meta::List<int, long>>));
}


namespace 
{
    template <typename... TS> struct WrapList{};

    struct Wrap
    {
        template <typename... TS> using f = WrapList<TS...>;
    };
}

TEST_CASE("test meta::PopFrontc")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::PopFrontc<0>::f<>, meta::List<>>));
    CHECK((std::is_same_v<meta::PopFrontc<0>::f<int>, meta::List<int>>));
    CHECK((std::is_same_v<meta::PopFrontc<0>::f<int, char>, meta::List<int, char>>));

    CHECK((std::is_same_v<meta::PopFrontc<1>::f<int>, meta::List<>>));
    CHECK((std::is_same_v<meta::PopFrontc<1>::f<int, char>, meta::List<char>>));

    CHECK((std::is_same_v<meta::PopFrontc<2>::f<int,char>, meta::List<>>));
    CHECK((std::is_same_v<meta::PopFrontc<2>::f<int, char,bool>, meta::List<bool>>));


    CHECK((std::is_same_v<meta::PopFrontc<0,Wrap>::f<>, WrapList<>>));
    CHECK((std::is_same_v<meta::PopFrontc<0,Wrap>::f<int>, WrapList<int>>));
    CHECK((std::is_same_v<meta::PopFrontc<0,Wrap>::f<int, char>, WrapList<int, char>>));

    CHECK((std::is_same_v<meta::PopFrontc<1,Wrap>::f<int>, WrapList<>>));
    CHECK((std::is_same_v<meta::PopFrontc<1,Wrap>::f<int, char>, WrapList<char>>));

    CHECK((std::is_same_v<meta::PopFrontc<2,Wrap>::f<int,char>, WrapList<>>));
    CHECK((std::is_same_v<meta::PopFrontc<2,Wrap>::f<int, char,bool>, WrapList<bool>>));
}

TEST_CASE("test meta::PopFront")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::PopFront<LC<0>>::f<>, meta::List<>>));
    CHECK((std::is_same_v<meta::PopFront<UC<0>>::f<int>, meta::List<int>>));
    CHECK((std::is_same_v<meta::PopFront<LC<1>>::f<int, char>, meta::List<char>>));
    CHECK((std::is_same_v<meta::PopFront<UC<2>>::f<int,char>, meta::List<>>));
}


TEST_CASE("test meta::PushFront")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::PushFront<>, meta::Listify>));
    CHECK((std::is_same_v<meta::PushFront<Wrap>, Wrap>));
}

TEST_CASE("test meta::Rotate")
{
    namespace meta = ugarit::meta;

    CHECK((std::is_same_v<meta::Rotatec<0>::f<>, meta::List<>>));
    CHECK((std::is_same_v<meta::Rotatec<0>::f<int>, meta::List<int>>));
    CHECK((std::is_same_v<meta::Rotatec<0>::f<long,int>, meta::List<long,int>>));

    CHECK((std::is_same_v<meta::Rotatec<1>::f<>, meta::List<>>));
    CHECK((std::is_same_v<meta::Rotatec<1>::f<int>, meta::List<int>>));
    CHECK((std::is_same_v<meta::Rotatec<1>::f<int,long>, meta::List<long,int>>));
    CHECK((std::is_same_v<meta::Rotatec<1>::f<int,long,char>, meta::List<long,char,int>>));

    CHECK((std::is_same_v<meta::Rotatec<2>::f<>, meta::List<>>));
    CHECK((std::is_same_v<meta::Rotatec<2>::f<int>, meta::List<int>>));

    CHECK((std::is_same_v<meta::Rotatec<2>::f<int,long>, meta::List<int,long>>));
    CHECK_MESSAGE((std::is_same_v<meta::Rotatec<2>::f<int,long,char>, meta::List<char,int,long>>), (demangle_t<meta::Rotatec<2>::f<int,long,char>>())); 
    CHECK_MESSAGE((std::is_same_v<meta::Rotatec<-1>::f<int,long,char>, meta::List<char,int,long>>), (demangle_t<meta::Rotatec<-1>::f<int,long,char>>()));

    CHECK((std::is_same_v<meta::Rotatec<0,Wrap>::f<>, WrapList<>>));
    CHECK((std::is_same_v<meta::Rotatec<1,Wrap>::f<int>, WrapList<int>>));
    CHECK_MESSAGE((std::is_same_v<meta::Rotatec<2,Wrap>::f<long,int>, WrapList<int,long>>),(demangle_t<meta::Rotatec<2,Wrap>::f<long,int>>())); 

    using X = meta::Rotatec<2>::f<int,long,char>;

    std::cout << "---\n" << testing::demangle_t<X>() << std::endl; 
}

