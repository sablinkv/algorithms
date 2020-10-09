#pragma once
#include <utils>
#include <search>

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate>
		inline void Binary_insertion_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			auto Second = std::next(First);
			auto Right = First;
			for (; ++Right != Last; ) {
				auto Left = std::prev(Right);
				auto Lowest = --algorithms::lower_bound(First, Left, *Right, Compare);

				while (Left != Lowest && Left != First) {
					auto Next = std::next(Left);
					if (!Compare(*Next, *Left))
						break;
					std::iter_swap(Next, Left);
					--Left;
				}

				if (Compare(*Second, *First))
					std::iter_swap(First, Second);
			}
		}
	} //namespace detail

	/*
		Binary insertion sort - STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2);
			Best		case - Ω(lgN).
		Space:
			Add			costs - O(1).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void binary_insertion_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Binary_insertion_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms