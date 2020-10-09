#pragma once
#include "heap_sort.hpp"
#include <utils>
#include <vector>
#include <algorithm>

#define LOAD_FACTOR_DEFAULT 0.75

namespace algorithms {
	namespace detail {
		template<class Forward_iterator, class Binary_predicate>
		void Bucket_sort_unchecked(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare, const double Load)
		{
			using value_type = iterator_value_t<Forward_iterator>;
			using buckets = std::vector<value_type>;

			const auto Bucket_count = static_cast<size_t>(std::distance(First, Last) / Load);
			const auto Offset = Compare(0, 1) ? 0 : Bucket_count - 1;
			auto Hasher = [Bucket_count, Offset](const auto Value) { 
				return static_cast<size_t>(std::abs(Offset - (Value * Bucket_count)));
			};
			std::vector<buckets> Table(Bucket_count);

			std::for_each(First, Last, [&Table, &Hasher](const value_type& Value) {
				const size_t Key = Hasher(Value);
				Table[Key].push_back(Value);
			});

			std::for_each(Table.begin(), Table.end(), [&Compare](std::vector<value_type>& Bucket) {
				Heap_sort_unchecked(Bucket.begin(), Bucket.end(), Compare);
			});

			std::for_each(Table.begin(), Table.end(), [&First](const std::vector<value_type>& Bucket) {
				First = std::copy(std::begin(Bucket), std::end(Bucket), First);
			});
		}

	} // namespace detail
	
	/*
		Bucket sort - STABLE (depends on bucket list sorting algorithm)
		Complexity:
			Worst		case - O(N^2) or O(N lgN) - depends on sorting a bucket list;
			Average		case - θ(N);
			Best		case - Ω(N).
		Space:
			Add			costs - O(N + k, where k depends on load factor).
	*/
	template<class Forward_iterator, class Binary_predicate,
		class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline void bucket_sort(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		using value_type = iterator_value_t<Forward_iterator>;
		static_assert(std::is_floating_point_v<value_type>, "Bucket sort - sorts only real types.");

		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Bucket_sort_unchecked(First, Last, Compare, LOAD_FACTOR_DEFAULT);
		}	
	}
} // namespace algorithms