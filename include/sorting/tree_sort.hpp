#pragma once
#include <utils>
#include <set>
#include <algorithm>

namespace algorithms {
	namespace detail {
		template<class Forward_iterator, class Binary_predicate>
		inline void Tree_sort_unchecked(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare)
		{
			using value_type = iterator_value_t<Forward_iterator>;
			std::multiset<value_type, Binary_predicate> temporary_tree(Compare);
			std::move(First, Last, std::insert_iterator(temporary_tree, temporary_tree.begin()));
			std::move(temporary_tree.begin(), temporary_tree.end(), First);
		}
	}

	/*
		Tree sort - STABLE
		Complexity:
			Worst		case - O(N^2);
			Average		case - θ(N lgN);
			Best		case - Ω(N lgN).
		Space:
			Add			costs - O(N).
	*/
	template<class Forward_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline void tree_sort(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Tree_sort_unchecked(First, Last, Compare);
		}
	}
	
} // namespace algorithms
