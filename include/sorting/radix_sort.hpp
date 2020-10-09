#pragma once
#include "counting_sort.hpp"
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Binary_predicate>
		void Radix_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			using value_type = iterator_value_t<Bidirectional_iterator>;

			const size_t DEC = 10;
			const auto Max = *std::max_element(First, Last);
			size_t Exp = 1;
			auto Hasher = [&Exp, DEC](const value_type& Value) { 
				return static_cast<size_t>((Value / Exp) % DEC);
			};

			while (Max / Exp) {
				Buffered_counting_sort(First, Last, Hasher, DEC);
				Exp *= DEC;
			}
			
			if (!Compare(*First, Max))
				std::reverse(First, Last);
		}
	} // namespace detail

	/*
		Radix sort - STABLE
		Complexity:
			Worst		case - O(N + k), where k is the max element of the input sequence;
			Average		case - θ(N + k);
			Best		case - Ω(N + k).
		Space:
			Add			costs - O(k).
	*/
	template<class Bidirectional_iterator, class Binary_predicate,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void radix_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		using value_type = iterator_value_t<Bidirectional_iterator>;
		static_assert(std::is_unsigned_v<value_type>, "Radix sort - sorts only unsigned integer types.");

		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Radix_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms