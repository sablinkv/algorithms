#pragma once
#include "heap_sort.hpp"
#include <utils>
#include <search>
#include <vector>
#include <stack>

namespace algorithms {
	namespace detail {
		template<class Random_iterator, class Binary_predicate>
		inline void Patience_sort_unchecked(Random_iterator First, Random_iterator Last, Binary_predicate Compare)
		{
			using value_type = iterator_value_t<Random_iterator>;
			using pile_type = std::stack<value_type>;

			std::vector<pile_type> Piles;
			auto Pred = [&Compare](const pile_type& Lhs, const value_type& Rhs) { 
						return Compare(Lhs.top(), Rhs); 
			};

			for (auto _First = First; _First != Last; ++_First) {
				auto Iter = algorithms::lower_bound(Piles.begin(), Piles.end(), *_First, Pred);
				if (Iter != Piles.end())
					Iter->push(*_First);
				else {
					pile_type temp_pile;
					temp_pile.push(*_First);
					Piles.push_back(std::move(temp_pile));
				}
			}

			const auto Extract_top([](pile_type &stack) {
				value_type Value = stack.top();
				stack.pop();
				return Value;
			});

			const auto Compare_top([&Compare](const pile_type &lhs, const pile_type &rhs) {
				return Compare(rhs.top(), lhs.top());
			});

			for (auto _First = First; _First != Last; ++_First) 
			{
				Pop_heap_unchecked(Piles.begin(), Piles.end(), Compare_top);

				auto Pile = &Piles.back();
				*_First = std::move(Extract_top(*Pile));
				
				if (Pile->empty())
					Piles.pop_back();
				else
					Push_heap_unchecked(Piles.begin(), Piles.end(), Compare_top);
			}
		}
	} // namespace detail

	/*
		Patience sort - NOT STABLE
		Complexity:
			Worst		case - O(N lgN);
			Average		case - θ(N lgN);
			Best		case - Ω(N).
		Space:
			Add			costs - O(N).
	*/
	template<class Random_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Random_iterator, std::random_access_iterator_tag>>
	>inline void patience_sort(Random_iterator First, Random_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		if (utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Patience_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms