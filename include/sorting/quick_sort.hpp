#pragma once
#include <utils>
#include "median_three.hpp"

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate, class Partition_type>
		void Quick_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare, Partition_type Partition)
		{
			if (utility::verify_range(First, Last, 1)) {
				auto Mid = Partition(First, Last, Compare);
				Quick_sort_unchecked(First, Mid, Compare, Partition);
				Quick_sort_unchecked(Mid, Last, Compare, Partition);
			}
		}
	} // namespace detail

	struct hoare_partition {
		template<class Bidirectional_iterator, class Binary_predicate>
		constexpr Bidirectional_iterator operator()(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare) const
		{
			auto Mid = utility::middle(First, --Last);
			detail::Median_three_unchecked(First, Mid, Last, Compare);
			const auto Pivot = *Mid;
			auto Left = First;
			auto Right = Last;
			
			while (true) {
				while (Compare(*Left, Pivot)) ++Left;
				while (Compare(Pivot, *Right)) --Right;
				
				auto Length1 = std::distance(First, Left);
				auto Length2 = std::distance(First, Right);

				if ((Length1 - Length2) < 0)
					std::iter_swap(Left++, Right--);
				else
					return ++Right;
			}
		}
	};

	struct lomuto_partition {
		template<class Bidirectional_iterator, class Binary_predicate>
		constexpr Bidirectional_iterator operator()(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare) const
		{
			auto Pivot = *--Last;
			auto Iter = First;
			
			for (auto _First = First; _First != Last; ++_First)
				if (Compare(*_First, Pivot))
					std::iter_swap(Iter++, _First);

			std::iter_swap(Iter, Last);
			if (Iter != First)
				--Iter;

			if (!utility::verify_range(First, Iter, 3)) {
				if (Compare(*Iter, *First))
					std::iter_swap(Iter, First);
			}
		
			return ++Iter;
		}
	};

	/*
		Quick sort Hoare partition - UNSTABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N lgN);
			Best		case - Ω(N lgN).
		Space:
			add			costs - O(lgN).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void quick_sort_hoare(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Quick_sort_unchecked(First, Last, Compare, hoare_partition());
		}
	}

	/*
		Quick sort Lomuto partition - UNSTABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N lgN);
			Best		case - Ω(N^2).
		Space:
			Add			costs - O(lgN).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void quick_sort_lomuto(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Quick_sort_unchecked(First, Last, Compare, lomuto_partition());
		}
	}

	template<class Bidirectional_iterator, class Binary_predicate = std::less<>, class Partition_type = hoare_partition,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void quick_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = {}, Partition_type Partition = {})
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Quick_sort_unchecked(First, Last, Compare, Partition);
		}
	}

} // namespace algorithms
