#pragma once
#include <utils>
#include "../sorting/merge_sort_buffered.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy>
        struct buffered_merge_sorter_impl {
            using iterator_category = std::forward_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Buffered merge sort require non-const and forward iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                merge_sort_buffered(First, Last, Compare);
            }
        };
    } // namespace detail

    using buffered_merge_sorter = sort_adapter<detail::buffered_merge_sorter_impl<policy::sequential_execute>>;

    template<>
    struct is_stable<buffered_merge_sorter> : std::true_type {};
} // namespace algorithms