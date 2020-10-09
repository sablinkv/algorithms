#pragma once
#include "insertion_sort.hpp"
#include <utils>
#define TIM_SORT_MAX 32

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate>
		void Tim_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			auto Length = std::distance(First, Last);
			auto RunTo = [] (Bidirectional_iterator From, Bidirectional_iterator To, const int Size) {
				if(utility::verify_range(From, To, Size))
					return std::next(From, Size);
				return To;
			};

			if (Length < TIM_SORT_MAX)
				return Insertion_sort_unchecked(First, Last, Compare);

			auto _First = First;
			while (_First != Last) {
				auto End = RunTo(_First, Last, TIM_SORT_MAX);
				Insertion_sort_unchecked(_First, End, Compare);
				_First = End;
			}

			for (auto Step = TIM_SORT_MAX; Step < Length; Step = Step << 1) {
				auto Left = First;
				while (Left != Last) {
					auto Mid = std::next(Left, Step);
					auto End = RunTo(Left, Last, Step << 1);
					std::inplace_merge(Left, Mid, End, Compare);

					if (!utility::verify_range(End, Last, Step))
						break;

					Left = End;
				}
			}
		}
	} // namespace detail

	/*
		Tim sort - STABLE
		Complexity:
			Worst		case - O(N lgN);
			Average		case - θ(N lgN);
			Best		case - Ω(N lgN).
		Space:
			Add			costs - O(1).
	*/
	template<class Bidirectional_iterator, class Binary_pedicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void tim_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_pedicate Compare = Binary_pedicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Tim_sort_unchecked(First, Last, Compare);
		}
	}

} // namespace algorithms