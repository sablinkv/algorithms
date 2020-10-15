#pragma once
#include <utils>
#include "../sorting/tim_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy>
        struct tim_sorter_impl {
            using iterator_category = std::bidirectional_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Tim sort require non-const and bidirectional iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                tim_sort(First, Last, Compare);
            }
        };
    } // namespace detail
    
    using tim_sorter = sort_adapter<detail::tim_sorter_impl<policy::sequential_execute>>;
    
    template<>
    struct is_stable<tim_sorter> : std::true_type {};
} // namespace algorithms