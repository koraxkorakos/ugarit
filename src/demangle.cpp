
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file
/// This file defines a function to demangle symbol names
///
/// \author Christian Kotz
/// \version 0.1 beta
/// \date 10/01/2020
///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                       \copyright Cargometer GesmbH 2020
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <testutils/demangle.hpp>
#include <string>

#ifdef __GNUG__
#include <cassert>
#include <cxxabi.h>
#include <sstream>

namespace {
std::string generateMessage(testing::DemanglingFailed::Cause cause,
                            char const symbolName[]) {
  using E = testing::DemanglingFailed;

  switch (cause) {
  case E::success:
    return "demagling succeeded";
  case E::outOfMemory:
    return "demagling failed: out of memory";
  case E::noMangledNamed: {
    std::stringstream msg;
    msg << "demagling failed: Invalid mangled name";
    if (symbolName) {
      msg << " '" << symbolName << '\'';
    }
    return msg.str();
  }
  case E::invalidArgument:
    return "demangling failed: invalid argument";
  default: {
    std::stringstream msg;
    msg << "demagling failed: unknown error " << (int)cause;
    if (symbolName) {
      msg << " on '" << symbolName << '\'';
    }
    return msg.str();
  }
  }
}
} // namespace

#endif

namespace testing {
#ifdef __GNUG__

DemanglingFailed::DemanglingFailed(Cause cause, char const symbol[])
    : std::runtime_error(generateMessage(cause, symbol)), cause(cause),
      symbol(symbol) {}

///\throw `DemanglingFailed`, std::bad_alloc`
std::string demangle(char const symbolName[]) {
  std::string result;
  int state;
  char *charArray = abi::__cxa_demangle(symbolName, nullptr, nullptr, &state);
  if (state) {
    throw DemanglingFailed(DemanglingFailed::Cause(state), symbolName);
  }
  assert(charArray);
  try {
    result = charArray;
    free(charArray);
  } catch (...) {
    free(charArray);
    throw;
  }

  return result;
}
#else
/// fallback for other compilers
std::string demangle(char const symbolName[]) { return symbolName; }
#endif
} // namespace testing
