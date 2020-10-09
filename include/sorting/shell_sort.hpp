#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate>
		inline void Shell_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			auto Index = std::distance(First, Last) >> 1;

			while (Index > 0) {
				for (auto Right = std::next(First, Index); Right != Last; ++Right) {
					auto _Right = Right;
					for(auto Left = std::prev(_Right, Index); 
						std::distance(First, _Right) >= Index && Compare(*_Right, *Left);
						Left = std::prev(Left, Index)
					)
					{
						std::iter_swap(_Right, Left);
						std::advance(_Right, -Index);
					}
				}
				Index = Index >> 1;
			}
		}
	} // namespace detail

	/*
		Shell sort - NOT STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N (lgN)^2);
			Best		case - Ω(N).
		Space:
			Add			costs - O(1).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void shell_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Shell_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms