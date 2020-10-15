#pragma once
#include <utils>
#include "../sorting/heap_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy>
        struct heap_sorter_impl {
            using iterator_category = std::random_access_iterator_tag;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Heap sort require non-const and random access iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                heap_sort(First, Last, Compare);
            }
        };
    } // namespace detail
    
    using heap_sorter = sort_adapter<detail::heap_sorter_impl<policy::sequential_execute>>;
} // namespace algorithms