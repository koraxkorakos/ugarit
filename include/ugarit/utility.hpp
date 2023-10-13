#include <concepts>
#include <cstdint>
#include <bit>

namespace ugarit{

///\brief return the number parity of the number of sign flip in combining two bit sets (for GA)
///\retval true  odd number of sign flips 
///\retval false even number of sign flips
constexpr auto reorder_parity(std::uintmax_t a, std::uintmax_t b) {
    std::uintmax_t result{};
    while(b <<= 1) {
        result ^= std::popcount(a & b) & 1U;
    }
    return result;
}

///\brief (-1)^n, where n is the number of sign flips in reordering bits a and b
///\retval -1 if odd number of sign flips
///\retval 1 if even number of sign flips
constexpr auto reorder_sign(std::uintmax_t a, std::uintmax_t b){
    return reorder_parity(a,b) ? -1 : 1;
}



}