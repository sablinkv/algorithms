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

	template <class Iterator, class = void>
	inline constexpr bool is_iterator_v = false;

	template <class Iterator>
	inline constexpr bool is_iterator_v<Iterator, std::void_t<iterator_category_t<Iterator>>> = true;

	template<class Iterator>
	using enable_if_iterator = std::enable_if_t<is_iterator_v<Iterator>>;

	template<class Iterator>
	using disable_if_iterator = std::enable_if_t<!is_iterator_v<Iterator>>;
	
	template<class Iterator>
	struct is_const_iterator {
		using pointer = typename std::iterator_traits<Iterator>::pointer;
		static constexpr bool value = std::is_const_v<typename std::remove_pointer<pointer>::type>;
	};

	template<class Iterator>
	inline constexpr bool is_const_iterator_v = is_const_iterator<Iterator>::value;

	template<class Current_iterator, class Required_iterator>
	struct is_sortable {
		static constexpr bool value = std::is_convertible_v<iterator_category_t<Current_iterator>, Required_iterator>
			&& !is_const_iterator_v<Current_iterator>;
	};

	template<class Current_iterator, class Required_iterator>
	inline constexpr bool is_sortable_v = is_sortable<Current_iterator, Required_iterator>::value;

	template<class Sorter>
	struct is_stable : std::false_type {};

	template<class Sorter>
	inline constexpr bool is_stable_v = is_stable<Sorter>::value;
} // namespace algorithms