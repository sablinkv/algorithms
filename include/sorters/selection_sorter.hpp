#pragma once
#include <utils>
#include "../sorting/selection_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy>
        struct selection_sorter_impl {
            using iterator_category = std::forward_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Selection sort require non-const and forward iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                selection_sort(First, Last, Compare);
            }
        };
    } // namespace detail

    using selection_sorter = sort_adapter<detail::selection_sorter_impl<policy::sequential_execute>>;
} // namespace algorithms