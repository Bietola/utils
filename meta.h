#pragma once

#include <tuple>

namespace utl {

// utility for building metafunctions that
// return types
template <class T>
struct type_of {
    using type = T;
};

// Function that returns its nth argument.
template <size_t nth, class... Args>
auto pick_nth_arg_impl(const std::tuple<Args...>& args) {
    return std::get<nth>(args);
}

template <size_t nth, class... Args>
auto pick_nth_arg(Args&&... args) {
    return pick_nth_arg_impl(std::forward(args)...);
}

}
