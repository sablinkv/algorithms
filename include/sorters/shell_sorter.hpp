#pragma once
#include <utils>
#include "../sorting/shell_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy>
        struct shell_sorter_impl {
            using iterator_category = std::bidirectional_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Shell sort require non-const and bidirectional iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                shell_sort(First, Last, Compare);
            }
        };
    } // namespace detail
    
    using shell_sorter = sort_adapter<detail::shell_sorter_impl<policy::sequential_execute>>;
} // namespace algorithms