#pragma once
#include <utils>

namespace algorithms {
    template<class Bidirectional_iterator, class T, class Binary_predicate = std::less<>>
    NODISCARD Bidirectional_iterator ternary_search(Bidirectional_iterator First, Bidirectional_iterator Last, const T& Value, Binary_predicate Comapre = Binary_predicate())
    {
        using difference_type = iterator_difference_t<Bidirectional_iterator>;
        if(First != Last) {
            const difference_type Offset = std::distance(First, Last) / 3;
            auto Mid1 = std::next(First, Offset);
            auto Mid2 = std::prev(Last - 1, Offset); 

            if (*Mid1 == Value) return Mid1;
            if (*Mid2 == Value) return Mid2;
    
            if (Comapre(Value, *Mid1))
                return ternary_search(First, Mid1, Value, Comapre);
            else if (Comapre(*Mid2, Value))
                return ternary_search(Mid2, Last, Value, Comapre);
            else 
                return ternary_search(Mid1, Mid2, Value, Comapre);
        }
        return Last;
    }
}