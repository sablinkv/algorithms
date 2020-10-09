#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate>
		inline void Shaker_sort_uncheked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			bool Swapped = true;
			std::advance(Last, -1);

			while(Swapped) {
				Swapped = false;
				for(auto Left = First; Left != Last; ++Left) {
					auto Right = std::next(Left);
					if(Compare(*Right, *Left))
					{
						std::iter_swap(Left, Right);
						Swapped = true;
					}
				}
				
				if(!Swapped) 
					break;
				
				Swapped = false;
				for(auto Right = Last; Right != First; --Right)
				{
					auto Left = std::prev(Right);
					if(Compare(*Right,*Left))
					{
						std::iter_swap(Right, Left);
						Swapped = true;
					}
				}
			}
		}
	} // namespace detail

	/*
		Shaker sort - STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N^2);
			Best		case - Ω(N).
		Space:
			Add			costs - O(1).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void shaker_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Shaker_sort_uncheked(First, Last, Compare);
		}
	}
	
} // namespace algorithms
