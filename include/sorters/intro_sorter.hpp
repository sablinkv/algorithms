#pragma once
#include <utils>
#include "../sorting/intro_sort.hpp"
#include "sorter_policy.hpp"
#include "sorter_adapter.hpp"

namespace algorithms {
    namespace detail {
        template<class Execute_policy, class Partition_policy = hoare_partition>
        struct intro_sorter_impl {
            using iterator_category = std::random_access_iterator_tag;
            using partition_type = Partition_policy;
        protected:
            template<class Iterator, class Pred>
            void execute(Iterator First, Iterator Last, Pred Compare) const {
                static_assert(is_sortable_v<Iterator, iterator_category>, "Intro sort require non-const and random access iterator or stronger");
                if constexpr (Execute_policy::parallel)
                    return /*execute parallel sort*/;
                intro_sort(First, Last, Compare, partition_type());
            }
        };
    } // namespace detail
    
    using intro_sorter = sort_adapter<detail::intro_sorter_impl<policy::sequential_execute>>;
} // namespace algorithms