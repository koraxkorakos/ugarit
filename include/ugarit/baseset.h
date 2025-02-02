#pragma once

#include <bitset>

template <size_t n>
constexpr int sgn(std::bitset<n> a, std::bitset<n> b)
{
    using std::bit_ceil;
    using std::bitset;

    size_t par = {};
    auto const m = bit_ceil(n);

    auto mask = std::bitset<n>{}.set(); // checker board mask

    for(auto k = bit_ceil(n); k >>= 1; )
    {
        mask ^= mask << k;
        par ^= (a & mask).count() & (b & ~mask).count(); 
    }
    auto const is_odd(par & 1U);
    return is_odd ? -1 : 1; // both counts odd
}