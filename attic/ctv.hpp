#pragma once
#include <concepts>
#include <cstdint>
#include <utility>
//#include <type_traits>
namespace ugarit
{
    namespace ctv ///< compile time vector
    {        
        // helper meta and highwe order meta functions
        template <bool> struct choose { template <typename, typename T> using f = T; };
        template <> struct choose<true> { template <typename T, typename> using f = T; };
        template <bool cond, typename T, typename F> using alternative = typename choose<cond>::template f<T,F>;
        template <bool cond, typename T, typename F> using alterative_t = typename alternative<cond,T,F>::type;



        using index_t = std::uintmax_t;
        template <index_t... n> using indices_t = std::integer_sequence<index_t, n...>; ///< index sequence

        template <index_t... ns>   
        constexpr bool is_unique_seq = std::is_sorted<std::less_equal<index_t>>({ns...});

        template <typename> struct is_nset : std::false_type{};
        template <index_t... ns> requires(is_unique_seq<ns...>) struct is_nset<indices_t<ns...>> : std::true_type{};

        template <typename T> concept nset = is_nset<T>::value; ///< an strictly monotonious ascending index sequence

        namespace details{
            ///\brief Metafunction that creates an nset from an index sequence ny sorting removing duplicates
            template <typename> struct make_unique; ///< intentionally undefined
#ifdef UGARINT_NOSTATIC
            ///\brief specialization for not already sorted and removed duplicates
            template <index_t... ns> 
            struct make_unique<indices_t<ns...>> {
                static constexpr auto data = []() {
                using namespace std;
                N arr[] = {ns...};
                //return span<unsigned const>(cbegin(arr), unique(begin(arr), end(arr)));
                constexpr auto end_iter = unique(begin(arr), end(arr));
                constexpr auto size = end_iter - begin(arr);
                std::array<index_t, size> result;
                copy(begin(arr), end_iter, begin(result));
                return result;
                }();
                using type = indices_t<data[ns]...>;
            };
#else
/// \url https://stackoverflow.com/questions/63347311/generate-a-new-integer-sequence-by-removing-duplicates?utm_source=pocket_shared
template <typename T, T... Ints>
constexpr auto unique_until_nonsorted(std::integer_sequence<T, Ints...>) {
  // constexpr structured bindings are not allow :(
  constexpr auto pair = [] {
    std::array<T, sizeof...(Ints)> arr{Ints...};
    // get last iterator of unique
    auto sorted_end = std::is_sorted_until(arr.begin(), arr.end());
    // unique until last iterator
    auto unique_end = std::unique(arr.begin(), sorted_end);
    // copy nonsorted elements to last iterator
    auto copy_end = std::copy(sorted_end, arr.end(), unique_end);
    // get final arr size
    auto size = std::distance(arr.begin(), copy_end);
    return std::pair{arr, size};
  }();
  constexpr auto arr  = pair.first;
  constexpr auto size = pair.second;
  // using template lambda to expand pack
  return [&arr]<std::size_t... Is>(std::index_sequence<Is...>) {
    return std::integer_sequence<T, arr[Is]...>{};
  }(std::make_index_sequence<size>{});
}              
#endif            
        }

        template <nset T> using make_nset = alterative_t<is_nset<T>, std::type_identity<T>, details::make_unique_<T>>;

        template <typename T>
        concept svector_base = nset<typename T::index_set>;

        template <typename T>
        concept svector_expr = svector_base<T> && requires(T const &t, index_t idx, std::size_t pos)
        {
            { t[idx] } -> std::convertible_to<typename T::value_type>; // access by index
            { t(pos) } -> std::convertible_to<typename T::value_type>; // access by position
        };

        template <typename T>
        concept svector_sink = svector_base<T> && requires(T &t, index_t idx, std::size_t pos)
        {
            { t.set[idx] } -> std::same_as<void>; // access by index
            { t.set(pos) } -> std::same_as<void>; // access by position
        };

        
    }
}