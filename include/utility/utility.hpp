#pragma once
#include <exception>
#include <algorithm>
#define NODISCARD [[nodiscard]]

namespace algorithms {

	namespace utility {
		template<class Forward_iterator>
		constexpr bool verify_range(Forward_iterator First, Forward_iterator Last, int Distance = 0)
		{
			return std::distance(First, Last) > Distance;
		}

		template<class Input_iterator, class Binary_predicate>
		constexpr void verify_comparator(Input_iterator Lhs, Input_iterator Rhs, Binary_predicate Pred)
		{
			// verify if comparator is less_equal, greate_equal or equal_to
			if (Pred(*Lhs, *Lhs))
				throw (std::domain_error("Invalid comparator."));

			// verify if comparator is not_equal_to
			if (Pred(*Lhs, *Rhs))
			{
				if (Pred(*Rhs, *Lhs))
					throw (std::domain_error("Invalid comparator."));
			}
		}

		template<class Forward_iterator>
		NODISCARD Forward_iterator middle(Forward_iterator First, Forward_iterator Last)
		{
			using difference_type = iterator_difference_t<Forward_iterator>;
			const auto Index = static_cast<difference_type>(std::distance(First, Last) / 2);
			return std::next(First, Index);
		}
	} // namespace utility

} // namespace algorithms
