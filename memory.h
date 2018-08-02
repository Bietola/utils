#pragma once

#include <memory>
#include <vector>

namespace utl {

// construct vector of unique_ptrs
template <class Base, class... Args>
auto make_unique_vector(Args&&... args) {
    std::vector<std::unique_ptr<Base>> retVal;

    retVal.reserve(sizeof...(args));
    (retVal.emplace_back(std::forward<Args>(args)), ...);

    return retVal;
}

}
