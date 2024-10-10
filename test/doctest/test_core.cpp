#include <doctest/doctest.h>
#include <type_traits>
#include <utility>

import ugarit;

TEST_CASE("index_set") {
    using namespace ugarit;
    CHECK(true == std::is_same_v<index_set<>, std::index_sequence<>>);
    CHECK(true == std::is_same_v<index_set<>, index_seq<>>);
    CHECK(true == std::is_same_v<index_set<1>, index_seq<1>>);
    CHECK(true == std::is_same_v<index_set<1,2>, index_seq<1,2>>);
    CHECK(true == std::is_same_v<index_set<2,1>, index_seq<1,2>>);
    CHECK(true == std::is_same_v<index_set<1,1,2>, index_seq<1,2>>);
    CHECK(true == std::is_same_v<index_set<1,2,1>, index_seq<1,2>>);

    CHECK(false == containes<index_set<>,1>);
}

TEST_CASE_TEMPLATE("int_set", T, char, signed char, unsigned char, short, unsigned short, int, unsigned, long unsigned long, long long, unsigned long, wchar_t){
    using namespace ugarit;
    CHECK(true == std::is_same_v<integer_set<T>, std::integer_sequence<T>>);
    CHECK(true == std::is_same_v<integer_set<T>, integer_seq<T>>);
    CHECK(true == std::is_same_v<integer_set<T,1>, integer_seq<T,1>>);
    CHECK(true == std::is_same_v<integer_set<T,1,2>, integer_seq<T,1,2>>);
    CHECK(true == std::is_same_v<integer_set<T,2,1>, integer_seq<T,1,2>>);
    CHECK(true == std::is_same_v<integer_set<T,1,1,2>, integer_seq<T,1,2>>);
    CHECK(true == std::is_same_v<integer_set<T,1,2,1>, integer_seq<T,1,2>>);
}

/*
TEST_CASE("index_seq") {
    using namespace ugarit;
    CHECK(true = std::is_same_v<index_set<>, index_seq<>>);
}*/