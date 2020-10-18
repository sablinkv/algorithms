#include "../include/tools.hpp"
#include <search>

#define LINEAR_SEARCH_BODY(Search, Container)       \
    auto First = Container.cbegin();                \
    auto Last = Container.cend();                   \
    for(auto Item = First; Item != Last; ++Item) {  \
        auto Found = Search(First, Last, *Item);    \
        ASSERT_EQ(Item, Found);                     \
    }

#define BINARY_SEARCH_BODY(Search, Container, Compare, Offset)  \
    auto First = Container.cbegin();                            \
    auto Last = Container.cend();                               \
    for(auto Item = First; Item != Last; ++Item) {              \
        auto Found = Search(First, Last, *Item, Compare);       \
        ASSERT_EQ(Item + Offset, Found);                        \
    }

template<class Derived>
class BaseSequence : public TypeRandomSequence<std::vector<int>> {
public:
    using random_sequence = TypeRandomSequence<std::vector<int>>;

    void SetUp() override {
        random_sequence::SetUp();
        SetOrder();
        auto last = std::unique(container.begin(), container.end());
        container.erase(last, container.end());
    }

    void SetOrder() { static_cast<Derived*>(this)->SetOrder(); }
    auto GetComparator() const { return static_cast<const Derived*>(this)->GetComparator(); }
};

class AscendingSequence : public BaseSequence<AscendingSequence> {
public:
    using comparator_type = std::less<>;
    
    void SetOrder() { std::sort(container.begin(), container.end(), comparator_type()); }
    comparator_type GetComparator() const { return comparator_type(); }
};

class DescendignSequence : public BaseSequence<DescendignSequence> {
public:
    using comparator_type = std::greater<>;
    
    void SetOrder() { std::sort(container.begin(), container.end(), comparator_type()); }
    comparator_type GetComparator() const {return comparator_type(); }
};

TYPED_TEST_SUITE_P(BaseSequence);

TYPED_TEST_P(BaseSequence, LinearSearch) {
    LINEAR_SEARCH_BODY(algorithms::linear_search, this->container);
}

TYPED_TEST_P(BaseSequence, RandomSearch) {
    LINEAR_SEARCH_BODY(algorithms::random_search, this->container);
}

TYPED_TEST_P(BaseSequence, LowerBound) {
    BINARY_SEARCH_BODY(algorithms::lower_bound, this->container, this->GetComparator(), 0);
}

TYPED_TEST_P(BaseSequence, UpperBound) {
    BINARY_SEARCH_BODY(algorithms::upper_bound, this->container, this->GetComparator(), 1);
}

TYPED_TEST_P(BaseSequence, BinarySearch) {
    BINARY_SEARCH_BODY(algorithms::binary_search, this->container, this->GetComparator(), 0);
}

TYPED_TEST_P(BaseSequence, JumpSearch) {
    BINARY_SEARCH_BODY(algorithms::jump_search, this->container, this->GetComparator(), 0);
}

TYPED_TEST_P(BaseSequence, ExponentialSearch) {
    BINARY_SEARCH_BODY(algorithms::exponential_search, this->container, this->GetComparator(), 0);
}

REGISTER_TYPED_TEST_SUITE_P(BaseSequence,
    LinearSearch,
    RandomSearch,
    LowerBound,
    UpperBound,
    BinarySearch,
    JumpSearch,
    ExponentialSearch
);

using Types = ::testing::Types<AscendingSequence, DescendignSequence>;
INSTANTIATE_TYPED_TEST_SUITE_P(DifferenceTypes, BaseSequence, Types);
