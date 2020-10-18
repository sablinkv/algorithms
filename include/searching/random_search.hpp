#pragma once
#include <utils>
#include <random>
#include <vector>

namespace algorithms {
	/*
        Random search
        Search algorithm for any sequence.
        Return last if no such element was found.
        Complexity:
			Worst		case - O(lgN);
			Average		case - θ(lgN);
			Best		case - Ω(1).
    */
	template<class Forward_iteartor, class T, class Random_device = std::random_device>
	NODISCARD Forward_iteartor random_search(Forward_iteartor First, Forward_iteartor Last, const T& Value, Random_device RDevice = {})
	{
		if(First != Last)
		{
			using difference_type = iterator_difference_t<Forward_iteartor>;
			const auto Length = std::distance(First, Last);
			
			std::vector<bool> Visited(Length, false);
			std::uniform_int_distribution<difference_type> Dist(0, Length - 1);
			
			int CountVisited = 0;
			while (CountVisited < Length)
			{
				auto Index = Dist(RDevice);
				if (!Visited[Index])
				{
					auto Found = std::next(First, Index);
					if (*Found == Value)
						return Found;
					else
					{
						Visited[Index] = true;
						++CountVisited;
					}
				}
			}
		}
		return Last;
	}
} // namespace algorithms