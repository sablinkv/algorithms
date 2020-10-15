#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate>
		void Stooge_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			using difference_type = iterator_difference_t<Bidirectional_iterator>;
			auto _Last = std::prev(Last);

			if (Compare(*_Last, *First))
				std::iter_swap(First, _Last);

			const auto Distance = std::distance(First, Last);

			if (Distance > 2) {
				auto Offset = static_cast<difference_type>(Distance / 3);
				Stooge_sort_unchecked(First, std::prev(Last, Offset), Compare);
				Stooge_sort_unchecked(std::next(First, Offset), Last, Compare);
				Stooge_sort_unchecked(First, std::prev(Last, Offset), Compare);
			}
		}
	} // namespace detail

	/*
		Stooge sort - UNSTABLE
		Complexity:
			Worst		case - O(N^2.71);
			Average		case - θ(N^2.71);
			Best		case - Ω(N^2.71).
		Space:
			Add			costs - O(1).
	*/
	template<class Bidirectional_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void stooge_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Stooge_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms