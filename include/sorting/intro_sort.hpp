#pragma once
#include "heap_sort.hpp"
#include "quick_sort.hpp"
#include "insertion_sort.hpp"
#include <utils>
#define INTRO_SORT_MAX 32

namespace algorithms {
	namespace detail {
		template<class Random_iterator, class Binary_predicate>
		inline void Intro_sort_unchecked(Random_iterator First, Random_iterator Last, Binary_predicate Compare, size_t Depth)
		{
			if (utility::verify_range(First, Last, INTRO_SORT_MAX)) {
				if (Depth == 0)
					return Heap_sort_unchecked(First, Last, Compare);
				
				--Depth;
				auto Mid = hoare_partition()(First, Last, Compare);
				Intro_sort_unchecked(First, Mid, Compare, Depth);
				Intro_sort_unchecked(Mid, Last, Compare, Depth);
			}
			else {
				Insertion_sort_unchecked(First, Last, Compare);
			}
		}
	} // namespace detail

	/*
		Intro sort - NOT STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N lgN);
			Best		case - Ω(N lgN).
		Space:
			Add			costs - O(lgN).
	*/
	template<class Random_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Random_iterator, std::random_access_iterator_tag>>
	>inline void intro_sort(Random_iterator First, Random_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		using difference_type = iterator_difference_t<Random_iterator>;
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			auto Depth = static_cast<difference_type>(std::log(std::distance(First, Last)) * 2);
			detail::Intro_sort_unchecked(First, Last, Compare, Depth);
		}
	}
} // namespace algorithms
