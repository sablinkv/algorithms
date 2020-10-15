#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Forward_iterator, class Binary_predicate>
		inline void Selection_sort_unckecked(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare)
		{
			for (auto Left = First; Left != Last; ++Left) {
				auto Min = std::min_element(Left, Last, Compare);
				if (Min != Left)
					std::iter_swap(Min, Left);
			}
		}
	} // namespace detail

	/*
		Selection sort - UNSTABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2);
			Best		case - Ω(N^2).
		Space:
			Add			costs - O(1).
	*/
	template<class Forward_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline void selection_sort(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Selection_sort_unckecked(First, Last, Compare);
		}
	}
} // namespace algorithms