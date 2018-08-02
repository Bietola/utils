#pragma once

#include <memory>
#include <vector>

namespace utl {

// construct vector of unique_ptrs
template <class T, class... Args>
auto make_unique_vector(Args&&... args) {
    std::vector<std::unique_ptr<T>> v;
    v.reserve(sizeof...(args));
    (v.emplace_back(std::make_unique<T>(std::forward<Args>(args))), ...);
    return v;
}

}
