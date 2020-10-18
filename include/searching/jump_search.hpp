#pragma once
#include <utils>
#include <cmath>
#include "binary_search.hpp"

namespace algorithms {
    /*
        Jump search (Block search)
        Search algorithm for sorted sequence.
        Return last if no such element was found.
        Complexity:
			Worst		case - O(sqrt(N));
			Average		case - θ(sqrt(N));
			Best		case - Ω(1).
    */
    template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
    NODISCARD Forward_iterator jump_search(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
    {
        using difference_type = iterator_difference_t<Forward_iterator>;
        
        if (First != Last) {
        auto Length = std::distance(First, Last) - 1;
        const auto Step = static_cast<difference_type>(std::floor(std::sqrt(Length)));
        auto Block = std::make_pair(First, std::next(First, Step));
        while (Length >= Step) {
            if (!Compare(*Block.second, Value))
                break;
            Length -= Step;
            Block.first = Block.second;
            std::advance(Block.second, Length < Step ? Length + 1 : Step);
        }

        if (Block.second != Last) ++Block.second;
        auto Found = algorithms::binary_search(Block.first, Block.second, Value, Compare);
        if (Found != Block.second) return Found;
    }
    return Last;
    }
} // namespace algorithms