#pragma once
#include <iterator>

namespace algorithms {
	template<class Iterator>
	using iterator_category_t = typename std::iterator_traits<Iterator>::iterator_category;

	template<class Iterator>
	using iterator_value_t = typename std::iterator_traits<Iterator>::value_type;

	template<class Iterator>
	using iterator_pointer_t = typename std::iterator_traits<Iterator>::pointer;

	template<class Iterator>
	using iterator_difference_t = typename std::iterator_traits<Iterator>::difference_type;

	template<class Iterator>
	struct is_const_iterator
	{
		using pointer = typename std::iterator_traits<Iterator>::pointer;
		static constexpr bool value = std::is_const<typename std::remove_pointer<pointer>::type>::value;
	};

	template<class Iterator>
	constexpr bool is_const_iterator_v = is_const_iterator<Iterator>::value;

	template<class Iterator, class Iterator_tag>
	struct is_sortable {
		static constexpr bool value = std::is_convertible_v<iterator_category_t<Iterator>, Iterator_tag>
			&& !is_const_iterator_v<Iterator>;
	};

	template<class Iterator, class Iterator_tag>
	constexpr bool is_sortable_v = is_sortable<Iterator, Iterator_tag>::value;

	template<class Sorter>
	struct is_stable : std::false_type {};

	template<class Sorter>
	constexpr bool is_stable_v = is_stable<Sorter>::value;
} // namespace algorithms