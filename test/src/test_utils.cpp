#include "../include/tools.hpp"
#include <utils>
#include <list>
#include <forward_list>

TEST(IsSortable, Pointer) {
    using namespace algorithms;
	using const_pointer = const int*;
	ASSERT_FALSE(static_cast<bool>(is_sortable_v<const_pointer, std::random_access_iterator_tag>));
	
	using pointer_type = int*;
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<pointer_type, std::random_access_iterator_tag>));
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<pointer_type, std::bidirectional_iterator_tag>));
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<pointer_type, std::forward_iterator_tag>));
}

TEST(IsSortable, RandomIterator) {
    using namespace algorithms;
	using const_iterator = typename std::vector<int>::const_iterator;
	ASSERT_FALSE(static_cast<bool>(is_sortable_v<const_iterator, std::random_access_iterator_tag>));

	using iterator_type = std::vector<int>::iterator;
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<iterator_type, std::random_access_iterator_tag>));
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<iterator_type, std::bidirectional_iterator_tag>));
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<iterator_type, std::forward_iterator_tag>));
}

TEST(IsSortable, BidirectionalIterator) {
    using namespace algorithms;
	using const_iterator = typename std::list<int>::const_iterator;
	ASSERT_FALSE(static_cast<bool>(is_sortable_v<const_iterator, std::bidirectional_iterator_tag>));

	using iterator_type = std::list<int>::iterator;
	ASSERT_FALSE(static_cast<bool>(is_sortable_v<iterator_type, std::random_access_iterator_tag>));
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<iterator_type, std::bidirectional_iterator_tag>));
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<iterator_type, std::forward_iterator_tag>));
}

TEST(IsSortable, ForwardIterator) {
    using namespace algorithms;
	using const_iterator = typename std::forward_list<int>::const_iterator;
	ASSERT_FALSE(static_cast<bool>(is_sortable_v<const_iterator, std::forward_iterator_tag>));

	using iterator_type = std::forward_list<int>::iterator;
	ASSERT_FALSE(static_cast<bool>(is_sortable_v<iterator_type, std::random_access_iterator_tag>));
	ASSERT_FALSE(static_cast<bool>(is_sortable_v<iterator_type, std::bidirectional_iterator_tag>));
	ASSERT_TRUE(static_cast<bool>(is_sortable_v<iterator_type, std::forward_iterator_tag>));
}

class ValidComparatorTest : public ComparatorTest {};

class InvalidComparatorTest: public ComparatorTest {};

TEST_P(ValidComparatorTest, VerifyComparator) {
	using algorithms::utility::verify_comparator;
	auto first = container.cbegin();
	auto second = container.cbegin() + 1;
	ASSERT_NO_THROW(verify_comparator(first, second, comparator));
	ASSERT_NO_THROW(verify_comparator(second, first, comparator));
}

TEST_P(InvalidComparatorTest, VerifyComparator) {
	using algorithms::utility::verify_comparator;
	auto first = container.cbegin();
	auto second = container.cbegin() + 1;
	ASSERT_THROW(verify_comparator(first, second, comparator), std::domain_error);
	ASSERT_THROW(verify_comparator(second, first, comparator), std::domain_error);
}

INSTANTIATE_TEST_CASE_P(UtilsTest, ValidComparatorTest,
	::testing::Values(
		std::less<>(), [](const auto& lhs, const auto& rhs){return lhs < rhs;},
		std::greater<>(), [](const auto& lhs, const auto& rhs){return lhs > rhs;})
);

INSTANTIATE_TEST_CASE_P(UtilsTest, InvalidComparatorTest,
	::testing::Values(std::less_equal<>(), [](const auto& lhs, const auto& rhs){return lhs <= rhs;},
		std::greater_equal<>(), [](const auto& lhs, const auto& rhs){return lhs >= rhs;},
		std::equal_to<>(), [](const auto& lhs, const auto& rhs){return lhs == rhs;},
		std::not_equal_to<>(), [](const auto& lhs, const auto& rhs){return lhs != rhs;})
);
