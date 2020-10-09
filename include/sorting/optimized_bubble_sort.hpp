#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Forward_iterator, class Binary_predicate>
		inline void Optimized_bubble_sort_unchecked(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare)
		{
			bool Sorted = false;
			while (!Sorted) {
				Sorted = true;
				auto Left = First;
				auto Right = First;

				while(Left != Last && ++Right != Last) {
					if (Compare(*Right, *Left)) {
						std::iter_swap(Left, Right);
						Sorted = false;
					}
					++Left;
				}
			}
		}
	} // namespace detail

	/*
		Optimized bubble sort - STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2);
			Best		case - Ω(N).
		Space:
			Add			costs - O(1).
	*/
	template<class Forward_iterator, class Binary_predicate = std::less<>,
			class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline void optimized_bubble_sort(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Optimized_bubble_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms
