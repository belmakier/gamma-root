#ifndef GAMROOT_UTILS_TUPLES_HH
#define GAMROOT_UTILS_TUPLES_HH

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
// auto l causes some complaints but has a purpose for enforcing
// iteration order

/* STD */
#include <tuple>

namespace GamR {
  namespace Utils {
    // https://ideone.com/j6dNE5
    // https://stackoverflow.com/questions/16387354/template-tuple-calling-a-function-on-each-element
    // Basically a missing feature in the language until C++17
    // Though be warned, in C++17 std::apply might have randomised order of
    // iteration This should be first element to last as expected.
#ifndef DOXYGEN_SHOULD_SKIP_THIS

    template <int... Is>
    struct seq {
    };

    template <int N, int... Is>
    struct gen_seq : gen_seq<N - 1, N - 1, Is...> {
    };

    template <int... Is>
    struct gen_seq<0, Is...> : seq<Is...> {
    };

    template <typename T, typename F, int... Is>
    void for_each(T &&t, F f, seq<Is...>)
    {
      auto l = {(f(std::get<Is>(t)), 0)...};
    }

    // Logical extension of above but for two tuples
    template <typename T1, typename T2, typename F, int... Is>
    void for_both(T1 &&t1, T2 &&t2, F f, seq<Is...>)
    {
      auto l = {(f(std::get<Is>(t1), std::get<Is>(t2)), 0)...};
    
    }
    template <typename T1, typename T2, typename F, int... Is, typename N>
    void for_both(T1 &&t1, T2 &&t2, F f, seq<Is...>, N n)
    {
      auto l = {(f(std::get<Is>(t1), std::get<Is>(t2), n), 0)...};
    }

    
#endif

    /**
     * @brief Applies function on each element of tuple.
     *
     * As tuples may be a heterogeneous container, the function must
     * be templated, or a lambda function utilizing auto for the input
     * parameter. The function must be able to act upon all the types
     * contained in the tuple.
     *
     * @param t Tuple of types Ts...
     * @param f Function of type void(T)
     */
    template <typename... Ts, typename F>
    void for_each_in_tuple(std::tuple<Ts...> &t, F f)
    {
      for_each(t, f, gen_seq<sizeof...(Ts)>());
    }

    /**
     * @brief Applies function taking both elements of tuple as
     * arguments.
     *
     * An extension of GamR::Utils::for_each_in_tuple.
     *
     * @param t1 First tuple
     * @param t2 Second tuple (length less than tuple 1)
     * @param f Function of type void(T1, T2)
     */
    template <typename T1, typename T2, typename F>
    void for_both_in_tuple(T1 &t1, T2 &t2, F f)
    {
      for_both(t1, t2, f, gen_seq<std::tuple_size<T1>::value>());
    }

    template <typename T1, typename T2, typename F, typename N>
    void for_both_in_tuple(T1 &t1, T2 &t2, F f, N n)
    {
      for_both(t1, t2, f, gen_seq<std::tuple_size<T1>::value>(), n);
    }

  } // namespace Utils
} // namespace GamR

#pragma GCC diagnostic pop

#endif
