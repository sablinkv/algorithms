#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Random_iterator, class Binary_predicate, class Diff_t>
		void Heapify(Random_iterator First, Diff_t Mid, Diff_t Length, Binary_predicate Compare)
		{
			Diff_t Left = Mid * 2 + 1;
			Diff_t Right = Left + 1;
			Diff_t Top = Mid;

			if (Left < Length && Compare(*(First + Top), *(First + Left)))
				Top = Left;
			
			if (Right < Length && Compare(*(First + Top), *(First + Right)))
				Top = Right;
			
			if (Top != Mid) {
				std::iter_swap(First + Mid, First + Top);
				Heapify(First, Top, Length, Compare);
			}
		}

		template<class Random_iterator, class Binary_predicate>
		void Pop_heap_unchecked(Random_iterator First, Random_iterator Last, Binary_predicate Compare)
		{
			using difference_type = iterator_difference_t<Random_iterator>;
			std::iter_swap(First, --Last);
			Heapify(First, difference_type(0), difference_type(Last - First), Compare);
		}

		template<class Random_iterator, class Binary_predicate>
		void Push_heap_unchecked(Random_iterator First, Random_iterator Last, Binary_predicate Compare)
		{
			using value_type = iterator_value_t<Random_iterator>;
			auto Length = std::distance(First, Last);
			if(Length >= 2) {
				value_type Value = std::move(*(Last - 1));
				auto Top = --Length;
				auto Mid = (Top - 1) >> 1;

				while ((Top > 0) && Compare(*(First + Mid), Value)) {
					*(First + Top) = std::move(*(First + Mid));
					Top = Mid;
					Mid = (Top - 1) >> 1;
				}

				*(First + Top) = std::move(Value);
			}
		}

		template<class Random_iterator, class Binary_predicate>
		void Make_heap_unchecked(Random_iterator First, Random_iterator Last, Binary_predicate Compare)
		{
			for(auto Iter = First; Iter != Last;)
				Push_heap_unchecked(First, ++Iter, Compare);
		}

		template<class Random_iterator, class Binary_predicate>
		void Heap_sort_unchecked(Random_iterator First, Random_iterator Last, Binary_predicate Compare)
		{
			Make_heap_unchecked(First, Last, Compare);
			auto _Last = Last;
			for (; _Last - First >= 2;)
				Pop_heap_unchecked(First, _Last--, Compare);
		}
	} // namespace detail

	/*
		Heap sort - NOT STABLE
		Complexity:
			Worst		case - O(N lgN);
			Average		case - θ(N lgN);
			Best		case - Ω(N lgN).
		Space:
			Add			costs - O(1).
	*/
	template<class Random_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Random_iterator, std::random_access_iterator_tag>>
	>inline void heap_sort(Random_iterator First, Random_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Heap_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms
