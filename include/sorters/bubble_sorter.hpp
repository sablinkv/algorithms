#pragma once
#include <utils>
#include "../sorting/bubble_sort.hpp"
#include "../sorting/optimized_bubble_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy>
        struct bubble_sorter_impl {
            using iterator_category = std::forward_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Bubble sort require non-const and forward iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                bubble_sort(First, Last, Compare);
            }
        };

        template<class Execute_policy>
        struct opt_bubble_sorter_impl {
            using iterator_category = std::forward_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Optimized bubble sort require non-const and forward iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                optimized_bubble_sort(First, Last, Compare);
            }
        };
    } // namespace detail

    using bubble_sorter = sort_adapter<detail::bubble_sorter_impl<policy::sequential_execute>>;
    using optimized_bubble_sorter = sort_adapter<detail::opt_bubble_sorter_impl<policy::sequential_execute>>;

    template<>
    struct is_stable<optimized_bubble_sorter> : std::true_type {};
} // namespace algorithms