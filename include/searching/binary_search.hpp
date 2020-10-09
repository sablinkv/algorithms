#pragma once
#include <utils>

namespace algorithms {
	namespace detail {
		template<class Forward_iterator, class T, class Binary_predicate>
		NODISCARD Forward_iterator Lower_bound(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare)
		{
			auto Found = First;
			auto Length = std::distance(First, Last);
			while (Length > 0)
			{
				const auto Index = Length >> 1;
				const auto Mid = std::next(Found, Index);

				if (Compare(*Mid, Value))
				{
					Found = std::next(Mid);
					Length = Length - (Index + 1);
				}
				else
					Length = Index;
			}
			return Found;
		}

		template<class Forward_iterator, class T, class Binary_predicate>
		NODISCARD Forward_iterator Upper_bound(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare)
		{
			auto Found = First;
			auto Length = std::distance(First, Last);

			while (Length > 0)
			{
				auto Index = Length >> 1;
				const auto Mid = std::next(Found, Index);
				if (Compare(Value, *Mid))
				{
					Length = Index;
				}
				else
				{
					Found = std::next(Mid);
					Length -= Index + 1;
				}
			}
			return Found;
		}

	} // namespace detail

	template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
	NODISCARD Forward_iterator lower_bound(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
	{
		return detail::Lower_bound(First, Last, Value, Compare);
	}

	template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
	NODISCARD Forward_iterator upper_bound(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
	{
		return detail::Upper_bound(First, Last, Value, Compare);
	}

	template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
	NODISCARD Forward_iterator binary_search(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
	{
		auto Found = detail::Lower_bound(First, Last, Value, Compare);
		if (Found != Last && Value == *Found)
			return Found;
		return Last;
	}
} // namespace algorithms