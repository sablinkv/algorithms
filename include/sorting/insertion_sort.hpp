#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate>
		inline void Insertion_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			auto _First = First;
			auto Second = ++First;
			for (; First != Last; ++First) {			
				auto Prev = First;
				for (auto Iter = First; --Prev != _First; --Iter) {
					if (!Compare(*Iter, *Prev))
						break;
					std::iter_swap(Prev, Iter);
				}

				if (Compare(*Second, *_First))
					std::iter_swap(_First, Second);
			}
		}
	} // namespace detail

	/*
		Insertion sort - STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2);
			Best		case - Ω(N).
		Space:
			Add			costs - O(1).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
			class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void insertion_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Insertion_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms