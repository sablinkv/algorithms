#pragma once
#include <utils>

namespace algorithms {
	namespace detail{
		template<class Bidirectional_iterator, class Binary_predicate>
		inline void Gnome_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			auto Left = First;
			auto End = Last--;
			while (Left != Last) {
				auto Next = Left;
				if (++Next != End) {
					if (Compare(*Next, *Left)) {
						std::iter_swap(Next, Left);
						if (Left != First)
							--Left;
					}
					else {
						++Left;
					}
				}
			}
		}	
	} // namespace detail

	/*
		Gnome sort - STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2);
			Best		case - Ω(n^2).
		Space:
			Add			costs - O(1).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void gnome_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Gnome_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms
