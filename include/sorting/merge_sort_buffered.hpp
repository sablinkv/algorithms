#pragma once
#include <utils>
#include <vector>
#include <algorithm>

namespace algorithms {
	namespace detail{
		template<class Forward_iterator, class Binary_predicate>
		void Merge_buffered(
			Forward_iterator First, Forward_iterator Mid, Forward_iterator Last,
			iterator_pointer_t<Forward_iterator> const Buffer, const ptrdiff_t Length,
			Binary_predicate Compare
		)
		{
			using pointer_type = iterator_pointer_t<Forward_iterator>;
			auto Left = First;
			auto Right = Mid;
			pointer_type Out = Buffer;

			while (Left != Mid && Right != Last) {
				auto Item = Compare(*Right, *Left) ? Right++ : Left++;
				*Out++ = std::move(*Item);
			}

			Out = std::move(Left, Mid, Out);
			std::move(Right, Last, Out);
			std::move(Buffer, Buffer + Length, First);
		}

		template<class Forward_iterator, class Binary_predicate>
		void Merge_sort_buffered_unchecked(
			Forward_iterator First, Forward_iterator Last,
			iterator_pointer_t<Forward_iterator> const Buffer, const ptrdiff_t Length,
			Binary_predicate Compare
		)
		{
			if (Length > 1) {
				const auto Length1 = Length >> 1;
				const auto Length2 = Length - Length1;
				auto Mid = std::next(First, Length1);
				Merge_sort_buffered_unchecked(First, Mid, Buffer, Length1, Compare);
				Merge_sort_buffered_unchecked(Mid, Last, Buffer, Length2, Compare);
				Merge_buffered(First, Mid, Last, Buffer, Length, Compare);
			}
		}
	} // namespace detail

	/*
	Merge sort external buffer - STABLE
	Complexity:
		Worst		case - O(N lgN);
		Average		case - θ(N lgN);
		Best		case - Ω(N lgN).
	Space:
		Add			costs - O(N).
	*/
	template<class Forward_iterator, class Binary_predicate = std::less<>,
		class = std::enable_if_t<is_sortable_v<Forward_iterator, std::forward_iterator_tag>>
	>inline void merge_sort_buffered(Forward_iterator First, Forward_iterator Last, Binary_predicate Compare = Binary_predicate())
	{
		using value_type = iterator_value_t<Forward_iterator>;
		auto Length = std::distance(First, Last);
		if (Length > 1) {
			utility::verify_comparator(First, std::next(First), Compare);
			std::vector<value_type> temporary_buffer(Length);
			detail::Merge_sort_buffered_unchecked(First, Last, temporary_buffer.data(), Length, Compare);
		}
	}
} // namespace algorithms