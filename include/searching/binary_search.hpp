#pragma once
#include <utils>

namespace algorithms {
 	/*
		Lower bound
		Finds the first element that is not less than (i.e. greate or equal to) value.
		Return last if no such element was found. 
		Complexity:
			Worst		case - O(lgN);
			Average		case - θ(lgN);
			Best		case - Ω(1).
	*/
	template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
	NODISCARD Forward_iterator lower_bound(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
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

	/*
		Upper bound
		Finds the first element that is greater than value.
		Return last if no such element was found. 
		Complexity:
			Worst		case - O(lgN);
			Average		case - θ(lgN);
			Best		case - Ω(1).
   	*/
	template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
	NODISCARD Forward_iterator upper_bound(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
	{
		auto Found = First;
		auto Length = std::distance(First, Last);

		while (Length > 0) {
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

	/*
        Binary search
        Search algorithm for sorted sequence.
		Return last if no such element was found. 
        Complexity:
			Worst		case - O(lgN);
			Average		case - θ(lgN);
			Best		case - Ω(1).
    */
	template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
	NODISCARD Forward_iterator binary_search(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
	{
		auto Found = algorithms::lower_bound(First, Last, Value, Compare);
		if (Found != Last && Value == *Found)
			return Found;
		return Last;
	}
} // namespace algorithms