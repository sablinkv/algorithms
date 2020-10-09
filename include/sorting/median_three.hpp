#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template <class Input_iterator, class Binary_predicate>
		void Median_three_unchecked(Input_iterator First, Input_iterator Mid, Input_iterator Last, Binary_predicate Compare)
		{
			--Last;
			if (Compare(*Mid, *First))
				std::iter_swap(Mid, First);

			if (Compare(*Last, *Mid)) {
				std::iter_swap(Last, Mid);

				if (Compare(*Mid, *First))
					std::iter_swap(Mid, First);
			}
		}
	} // namespace detail

	template<class Input_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Input_iterator, std::input_iterator_tag>>
	>inline constexpr void median_three(Input_iterator First, Input_iterator Mid, Input_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (First != Last && Mid != Last) {
			utility::verify_comparator(First, Mid, Compare);
			detail::Median_three_unchecked(First, Mid, Last, Compare);
		}		
	}

	template<class Forward_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline constexpr void median_three(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 2)) {
			utility::verify_comparator(First, std::next(First), Compare);
			auto Mid = utility::middle(First, Last);
			detail::Median_three_unchecked(First, Mid, Last, Compare);
		}
	}
} // namespace algorithms