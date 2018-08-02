#include <tuple>

namespace utl::tpl {

template <class BinaryPredicate, class... Tuples, size_t n>
auto parallel_transform_n(Tuples&&... tuples, const BinaryPredicate& op) {
    return op(std::get<n>(tuples)...);
}

template <class BinaryPredicate, class... Tuples, size_t n,
          size_t I = std::make_index_sequence<N>>
auto parallel_transform(Tuples&&... tuples, const BinaryPredicate& op,
                        std::index_sequence<I>) {
    return std::make_tuple(parallel_transform_n<I>(tuples, op))...;
}

}
