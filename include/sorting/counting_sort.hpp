#pragma once
#include <utils>
#include <search>
#include <algorithm>
#include <cmath>

namespace algorithms {
	namespace detail {
		template<class Bidirectional_iterator, class Hesher>
		void Buffered_counting_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Hesher Hasher, const size_t Bucket_count)
		{
			using value_type = iterator_value_t<Bidirectional_iterator>;
			
			std::vector<size_t> Counter(Bucket_count, 0);
			std::for_each(First, Last, [&Counter, &Hasher](const value_type& Value) {
				const auto Key = Hasher(Value);
				++Counter[Key];
			});

			for (auto Iter = Counter.begin() + 1; Iter != Counter.end(); ++Iter)
				*Iter += *(Iter - 1);

			std::vector<value_type> Buffer(std::distance(First, Last));
			auto RLast = std::reverse_iterator(First);
			auto RFirst = std::reverse_iterator(Last);

			std::for_each(RFirst, RLast, [&](const value_type& Value) {
				const auto Key = Hasher(Value);
				const auto Index = Counter[Key] - 1;
				Buffer[Index] = Value;
				--Counter[Key];
			});

			std::copy(Buffer.begin(), Buffer.end(), First);
		}

		template<class Bidirectional_iterator, class Binary_predicate>
		void Counting_sort_unchecked(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare)
		{
			using value_type = iterator_value_t<Bidirectional_iterator>;
			auto [Min, Max] = std::minmax_element(First, Last, Compare);
			int64_t Offset = (*Min) * -1;
			const auto Bucket_count = static_cast<size_t>(std::abs(*Max + Offset)) + 1;

			auto Hesher = [Offset](const value_type& Value) { 
				return static_cast<size_t>(std::abs(Value + Offset)); 
			};
			Buffered_counting_sort(First, Last, Hesher, Bucket_count);
		}
	} // namespace detail

	/*
		Counting sort - STABLE
		Complexity:
			Worst		case - O(N + k), where 'k' is the max element of the input sequence;
			Average		case - θ(N + k);
			Best		case - Ω(N + k).
		Space:
			Add			costs - O(N + k).
	*/
	template<class Bidirectional_iterator, class Binary_predicate,
		class = std::enable_if_t<is_sortable_v<Bidirectional_iterator, std::bidirectional_iterator_tag>>
	>inline void counting_sort(Bidirectional_iterator First, Bidirectional_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		using value_type = iterator_value_t<Bidirectional_iterator>;
		static_assert(std::is_integral_v<value_type>, "Counting sort - sorts only integer types.");
		if(utility::verify_range(First, Last, 1)) {
			utility::verify_comparator(First, std::next(First), Compare);
			detail::Counting_sort_unchecked(First, Last, Compare);
		}
	}
} // namespace algorithms
