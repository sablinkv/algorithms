#pragma once
#include <utils>
#define SHRINK_FACTOR_DEFAULT 1.2473

namespace algorithms {
	namespace detail {
		template<class Forward_iterator, class Binary_predicate>
		inline void Comb_sort_uncheked(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare, const double Factor = SHRINK_FACTOR_DEFAULT)
		{
			using difference_type = iterator_difference_t<Forward_iterator>;
			const auto Length = std::distance(First, Last);
			auto Gap = Length - 1;
			bool Swapped = true;

			while ((Gap > 1) || Swapped) {
				if (Gap > 1)
					Gap = static_cast<difference_type>(Gap / Factor);
	
				Swapped = false;
				auto Left = First;
				auto Right = std::next(First, Gap);

				while(Right != Last) {
					if(Compare(*Right, *Left)) {
						std::iter_swap(Left, Right);
						Swapped = true;
					}
					++Right;
					++Left;
				}
			}
		}
	} // namespace detail

	/*
		Comb sort - UNSTABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2 / 2^p), where 'p' is a number of increment;
			Best		case - Ω(N lgN).
		Space:
			Add			costs - O(1).
	*/
	template<class Forward_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline void comb_sort(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Comb_sort_uncheked(First, Last, Compare);
		}
	}
} // namespace algorithms
