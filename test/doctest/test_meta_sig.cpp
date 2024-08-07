#include <doctest/doctest.h>
// ugarit:meta;
#include <iostream>
#include <type_traits>
#include <ugarit/meta_sig.hpp>
// check header guard
#include <testutils/demangle.hpp>
#include <ugarit/meta.hpp>

using testing::demangle;
using testing::demangle_t;

TEST_CASE("ugarit_meta_sig, is_NSequence") {
  namespace meta = ugarit::meta;
  using meta::is_NSequence;
  using meta::NSequence;

  struct Dummy {};

  CHECK(false == is_NSequence<Dummy>::value);
  CHECK(true == is_NSequence<NSequence<>>::value);
  CHECK(true == is_NSequence<NSequence<0>>::value);
  CHECK(true == (is_NSequence<NSequence<2, 2>>::value));
  CHECK(true == (is_NSequence<NSequence<2, 1>>::value));
}

TEST_CASE("ugarit_meta_sig, is_unique_seq") {
  namespace meta = ugarit::meta;
  using meta::is_NSequence;
  using meta::is_unique_seq;
  using meta::NSequence;

  struct Dummy {};

  CHECK(false == is_NSequence<Dummy>::value);
  CHECK(true == is_NSequence<NSequence<>>::value);
  CHECK(true == is_NSequence<NSequence<0>>::value);
  CHECK(false == (is_NSequence<NSequence<2, 2>>::value));
  CHECK(false == (is_NSequence<NSequence<2, 1>>::value));
  CHECK(false == (is_NSequence<NSequence<2, 3, 2>>::value));
}

#ifdef META_CONCEPT_CHECK

TEST_CASE("ugarit_meta_sig, BSeq") {
  namespace meta = ugarit::meta;
  using meta::NSeq;
  using meta::NSequence;

  struct Dummy {};

  CHECK(false == NSeq<Dummy>);
  CHECK(true == NSeq<NSequence<>>);
  CHECK(true == NSeq<NSequence<1>>);
  CHECK(true == (NSeq<NSequence<1, 2>>));
  CHECK(true == (NSeq<NSequence<1, 1>>));
  CHECK(true == (NSeq<NSequence<1, 0>>));
}

TEST_CASE("ugarit_meta_sig, NSet") {
  namespace meta = ugarit::meta;
  using meta::NSequence;
  using meta::NSet;

  struct Dummy {};

  CHECK(false == NSet<Dummy>);
  CHECK(true == NSet<NSequence<>>);
  CHECK(true == NSet<NSequence<1>>);
  CHECK(true == (NSet<NSequence<1, 2>>));
  CHECK(false == (NSet<NSequence<1, 1>>));
  CHECK(false == (NSet<NSequence<1, 0>>));
  CHECK(false == (NSet<NSequence<1, 0, 1>>));
}

#endif