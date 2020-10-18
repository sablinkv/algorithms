#pragma once
#include <utils>
#include "binary_search.hpp"

namespace algorithms {
    /*
        Exponential search
        Search algorithm for sorted sequence.
        Return last if no such element was found. 
        Complexity:
			Worst		case - O(lgN);
			Average		case - θ(lgN);
			Best		case - Ω(1).
    */
    template<class Forward_iterator, class T, class Binary_predicate = std::less<>>
    NODISCARD Forward_iterator exponential_search(Forward_iterator First, Forward_iterator Last, const T& Value, Binary_predicate Compare = Binary_predicate())
    {
        using difference_type = iterator_difference_t<Forward_iterator>;
        if (First != Last) {
            difference_type Offset = 1;
            const auto Length = std::distance(First, Last);
            auto Range = std::make_pair(First, std::next(First, Offset));
            while (Range.second != Last && Compare(*Range.second, Value)) {
                std::advance(Range.first, Offset);
                Offset *= 2;
                std::advance(Range.second, std::min(Offset, Length - Offset));
            }
            return algorithms::binary_search(Range.first, Range.second, Value, Compare);
        }
        return Last;
    }
} // namespace algorithms