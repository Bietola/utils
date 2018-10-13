#pragma once

#include <type_traits>

#include "meta.h"

namespace utl {

// alternative to void which is
// a regular type
struct void_type {};

std::ostream& operator<<(std::ostream& ostream, const void_type&) {
    ostream << "{void_type}";
    return ostream;
}

// alternatives to std::invoke, but treating void as a
// regular type (by returning void_type, which is regular)
template <class Fun, class = void, class... Args>
struct void_invoke_result : std::invoke_result<Fun, Args...> {};

template <class Fun, class... Args>
struct void_invoke_result<Fun,
                          std::enable_if_t<
                              std::is_void_v<
                                  std::invoke_result_t<Fun, Args...>
                              >
                          >,
                          Args...> : type_of<void_type> {};

template <class Fun, class... Args>
using void_invoke_result_t = typename void_invoke_result<Fun, void, Args...>::type;

template <class Fun, class... Args,
          class Result = void_invoke_result_t<Fun, Args...>>
Result void_invoke(Fun&& fun, Args&&... args) {
    // TODO: maybe add macro to avoid repetition of std::invoke
    if constexpr(std::is_same_v<Result, void_type>) {
        std::invoke(std::forward<Fun>(fun),
                    std::forward<Args>(args)...);
        return {};
    }
    else {
        return std::invoke(std::forward<Fun>(fun),
                           std::forward<Args>(args)...);
    }
}

}
