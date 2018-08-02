#pragma once

#include <iterator>
#include <type_traits>
#include <functional>
#include "meta.h"

namespace utl {

// Computes set_symmetric_difference and set_intersection
// simultaneously.
//     convention: if no intersection aggregator is specified, lhs is chosen.
template <class InItrL, class InItrR,
          class OutItrIntr, class OutItrDiff,
          class Comp,
          class InValL = class std::iterator_traits<InItrL>::value_type,
          class InValR = class std::iterator_traits<InItrR>::value_type>
void set_decompose(InItrL rhs_begin, InItrL rhs_end,
                   InItrR lhs_begin, InItrR lhs_end,
                   OutItrDiff diff_begin,
                   OutItrIntr intr_begin,
                   Comp comp) {
    auto rhs_itr = rhs_begin;
    auto lhs_itr = lhs_begin;
    auto diff_itr = diff_begin;
    auto intr_itr = intr_begin;

    for(;rhs_itr != rhs_end && lhs_itr != lhs_end;){

        if(comp(*rhs_itr, *lhs_itr)) {
            *intr_itr = *lhs_itr, *rhs_itr;
        }
        else {
            *diff_itr = *rhs_itr;
            *diff_itr = *lhs_itr;
        }
    }

    auto [residual_itr, residual_end] = lhs_itr == lhs_end ?
                                        std::make_pair(rhs_itr, rhs_end) :
                                        std::make_pair(lhs_itr, lhs_end);
    std::copy(residual_itr, residual_end, diff_itr);
}

}
