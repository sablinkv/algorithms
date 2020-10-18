#pragma once
#include <utils>

namespace algorithms {
	/*
        Jump search (Block search)
        Search algorithm for any sequence.
        Return last if no such element was found.
        Complexity:
			Worst		case - O(N);
			Average		case - θ(N);
			Best		case - Ω(1).
    */
	template<class Forward_iterator, class T>
	NODISCARD Forward_iterator linear_search(Forward_iterator First, Forward_iterator Last, const T& Value)
	{
		auto Found = First;
		while(Found != Last && *Found != Value)
			++Found;
		return Found;
	}
} // namespace algorithms