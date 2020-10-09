#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Forward_iterator, class Binary_predicate>
		inline void Bubble_sort_unchecked(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare)
		{
			for (auto Left = First; Left != Last; ++Left)
			{
				for (auto Right = Left; ++Right != Last; )
				{
					if (Compare(*Right, *Left))
						std::iter_swap(Left, Right);
				}
			}
		}
	} // namespace detail

	/*
		Bubble sort - NOT STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2);
			Best		case - Ω(N^2).
		Space:
			Add			costs - O(1).
	*/
	template<class Forward_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline void bubble_sort(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Bubble_sort_unchecked(First, Last, Compare);
		}
	}	
} // namespace algorithms