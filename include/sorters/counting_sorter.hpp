#pragma once
#include <utils>
#include "../sorting/counting_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy>
        struct counting_sorter_impl {
            using iterator_category = std::bidirectional_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Counting sort require non-const and bidirectional iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                counting_sort(First, Last, Compare);
            }
        };
    } // namespace detail

    using counting_sorter = sort_adapter<detail::counting_sorter_impl<policy::sequential_execute>>;
    
    template<>
    struct is_stable<counting_sorter> : std::true_type {};
} // namespace algorithms
