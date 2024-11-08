#include <doctest/doctest.h>
#include <type_traits>
#include <utility>
#include <ugarit/meta.h>

TEST_CASE("is_homogeneous") 
{
    using ugarit::is_homogeneous;
    CHECK(false == is_homogeneous<1, 1U>);
    CHECK(true == is_homogeneous<1>);
    CHECK(true == is_homogeneous<1,2>);
    CHECK(true == is_homogeneous<>);
}

TEST_CASE("list") 
{    
    using ugarit::sequence;
    using ugarit::set;
    using ugarit::list;


    sequence<> s1;
    sequence<1> s2;
    sequence<2,1> s3;
    sequence<1,1U> s4;

    list<> s5;
    list<1> s6;
    list<2,1> s7;
    list<2,2> s88;    

    set<> s9;
    set<1> s10;
    set<1,2> s11;
}

#if 0

TEST_CASE("index_set") {
    using ugarit::index_seq;
    using ugarit::index_set;
    CHECK(true == std::is_same_v<index_set<>, std::index_sequence<>>);
    CHECK(true == std::is_same_v<index_set<>, index_seq<>>);
    CHECK(true == std::is_same_v<index_set<1>, index_seq<1>>);
    CHECK(true == std::is_same_v<index_set<1,2>, index_seq<1,2>>);
    CHECK(true == std::is_same_v<index_set<2,1>, index_seq<1,2>>);
    CHECK(true == std::is_same_v<index_set<1,1,2>, index_seq<1,2>>);
    CHECK(true == std::is_same_v<index_set<1,2,1>, index_seq<1,2>>);
}

TEST_CASE_TEMPLATE("int_set", T, char, signed char, unsigned char, short, unsigned short, int, unsigned, long unsigned long, long long, unsigned long, wchar_t){
    using ugarit::index_seq;
    using ugarit::index_set;
    using ugarit::at;
    using ugarit::contains;
    using ugarit::pos;

    CHECK(true == std::is_same_v<integer_set<T>, std::integer_sequence<T>>);
    CHECK(true == std::is_same_v<integer_set<T>, integer_seq<T>>);
    CHECK(true == std::is_same_v<integer_set<T,1>, integer_seq<T,1>>);
    CHECK(true == std::is_same_v<integer_set<T,1,2>, integer_seq<T,1,2>>);
    CHECK(true == std::is_same_v<integer_set<T,2,1>, integer_seq<T,1,2>>);
    CHECK(true == std::is_same_v<integer_set<T,1,1,2>, integer_seq<T,1,2>>);
    CHECK(true == std::is_same_v<integer_set<T,1,2,1>, integer_seq<T,1,2>>);

    CHECK(false == contains<integer_seq<T>,1>);
    CHECK(true == contains<integer_seq<T,1>,1>);
    CHECK(false == contains<integer_seq<T,1>,0>);
    CHECK(false == contains<integer_seq<T,1,2>,1>);
    CHECK(false == contains<integer_seq<T,1,2>,2>);

    CHECK(-1 == pos<integer_seq<T>,1>);
    CHECK(0 == pos<integer_seq<T,1>,1>);
    CHECK(-1 == pos<integer_seq<T,1>,0>);
    CHECK(0 == pos<integer_seq<T,1,2>,1>);
    CHECK(1 == pos<integer_seq<T,1,2>,2>);
    CHECK(0 == pos<integer_seq<T,1,1>,1>);
    CHECK(1 == pos<integer_seq<T,1,2,1>,2>);
    CHECK(0 == pos<integer_seq<T,1,2,1>,1>);

    CHECK(true == std::is_same_v<T const, declytpe(at<integer_seq<T,1>,0>));

    CHECK(T{1} == at<integer_seq<T,1>,0>);
    CHECK(T{1} == at<integer_seq<T,0,1>,1>);
    CHECK(T{2} == at<integer_seq<T,2,1>,0>);
    CHECK(T{2} == at<integer_seq<T,1,2>,1>);
    CHECK(T{3} == at<integer_seq<T,1,2,3>,2>);
    CHECK(T{1} == at<integer_seq<T,1,1>,1>);
    CHECK(T{1} == at<integer_seq<T,1,2,1>,2>);
    CHECK(T{2} == at<integer_seq<T,1,2,1>,1>);
}

TEST_CASE("bool_set"){
    
    using ugarit::index_seq;
    using ugarit::index_set;
    using ugarit::at;
    using ugarit::contains;
    using ugarit::pos;

    CHECK(true == std::is_same_v<integer_set<bool>, std::integer_sequence<bool>>);    
    CHECK(true == std::is_same_v<integer_set<bool>, std::integer_seq<bool>>);    
    CHECK(true == std::is_same_v<integer_set<bool,true>, std::integer_seq<bool,true>>);    
    CHECK(true == std::is_same_v<integer_set<bool,true>, std::integer_seq<bool,true,true>>);    
    CHECK(true == std::is_same_v<integer_set<bool,false>, std::integer_seq<bool,false>>);    
    CHECK(true == std::is_same_v<integer_set<bool,false>, std::integer_seq<bool,false,false>>);    
    CHECK(true == std::is_same_v<integer_set<bool,false,true>, std::integer_seq<bool,false,true>>);    
    CHECK(true == std::is_same_v<integer_set<bool,false,true>, std::integer_seq<bool,true,false>>);    
    CHECK(true == std::is_same_v<integer_set<bool,false,true>, std::integer_seq<bool,true,false,true>>);    

    CHECK(false == contains<integer_set<bool>, false>);
    CHECK(false == contains<integer_set<bool>, true>);
    CHECK(true == contains<integer_set<bool,true>,true>);
    CHECK(false == contains<integer_set<bool,true>,false>);
    CHECK(false == contains<integer_set<bool,true,true>,false>);
    CHECK(false == contains<integer_set<bool,false,true>,true>);
}

/*
TEST_CASE("index_seq") {
    using namespace ugarit;
    CHECK(true = std::is_same_v<index_set<>, index_seq<>>);
}*/
#endif