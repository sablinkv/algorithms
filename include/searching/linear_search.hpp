#pragma once
#include <utils>

namespace algorithms {
	template<class Forward_iterator, class T>
	NODISCARD Forward_iterator linear_search(Forward_iterator First, Forward_iterator Last, const T& Value)
	{
		auto Found = First;
		while(Found != Last && *Found != Value)
			++Found;
		return Found;
	}
} // namespace algorithms