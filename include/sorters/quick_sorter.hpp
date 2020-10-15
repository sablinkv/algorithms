#pragma once
#include <utils>
#include "../sorting/quick_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy, class Partition_policy = hoare_partition>
        struct quick_sorter_impl {
            using iterator_category = std::bidirectional_iterator_tag;
            using partition_type = Partition_policy;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Quick sort require non-const and bidirectional iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                quick_sort(First, Last, Compare, partition_type());
            }
        };
    } // namespace detail

    using quick_sorter = sort_adapter<detail::quick_sorter_impl<policy::sequential_execute>>;
    using quick_sorter_lomuto = sort_adapter<detail::quick_sorter_impl<policy::sequential_execute, lomuto_partition>>;
} // namespace algorithms