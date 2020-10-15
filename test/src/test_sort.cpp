#include "../include/tools.hpp"
#include <sort>
#include <vector>
#include <list>
#include <forward_list>

#define SORT_TEST_BODY(Sort, Container, Pred)           \
    auto First = Container.begin();                     \
    auto Last = Container.end();                        \
    const auto Size = std::distance(First, Last);       \
    Sort(First, Last, Pred);                            \
    ASSERT_TRUE(std::is_sorted(First, Last, Pred));     \
    ASSERT_EQ(std::distance(First, Last), Size)

#define SORT_TEST_P(TestSuiteName, TestName, Sort)                  \
TEST_P(TestSuiteName, TestName##_LESS) {                            \
    SORT_TEST_BODY(Sort, container, std::less<>());                 \
}                                                                   \
TEST_P(TestSuiteName, TestName##_GREATER) {                         \
    SORT_TEST_BODY(Sort, container, std::greater<>());              \
}                                                                   \
TEST_P(TestSuiteName, TestName##_LAMBDA) {                          \
    SORT_TEST_BODY(Sort, container, [](auto&& lhs, auto&& rhs) {    \
        return lhs < rhs;                                           \
    });                                                             \
}

template<class Container>
class ParamRandomSequence : public TypeRandomSequence<Container>, public ::testing::WithParamInterface<int> {
public:
    virtual void SetUp() override {
        const auto lenght = GetParam();
        this->Fill(lenght);
    }

    virtual ~ParamRandomSequence() {}
};

class RandomIteratorTest : public ParamRandomSequence<std::vector<uint16_t>> {};
class BidirectionalIteratorTest : public ParamRandomSequence<std::list<uint16_t>> {};
class ForwardIteratorTest : public ParamRandomSequence<std::forward_list<uint16_t>> {};

// for bucket sort
class RandomIteratorTestFloat : public ParamRandomSequence<std::vector<float>> {};
class BidirectionalIteratorTestFloat : public ParamRandomSequence<std::list<float>> {};
class ForwardIteratorTestFloat : public ParamRandomSequence<std::forward_list<float>> {};

// Binary insertion sort test
SORT_TEST_P(RandomIteratorTest, BinaryInsertionSort, algorithms::binary_insertion_sort)
SORT_TEST_P(BidirectionalIteratorTest, BinaryInsertionSort, algorithms::binary_insertion_sort)

// Bubble sort test
SORT_TEST_P(RandomIteratorTest, BubbleSort, algorithms::bubble_sort)
SORT_TEST_P(BidirectionalIteratorTest, BubbleSort, algorithms::bubble_sort)
SORT_TEST_P(ForwardIteratorTest, BubbleSort, algorithms::bubble_sort)

// Bucket sort test
SORT_TEST_P(RandomIteratorTestFloat, BucketSort, algorithms::bucket_sort)
SORT_TEST_P(BidirectionalIteratorTestFloat, BucketSort, algorithms::bucket_sort)
SORT_TEST_P(ForwardIteratorTestFloat, BucketSort, algorithms::bucket_sort)

// Comb sort test
SORT_TEST_P(RandomIteratorTest, CombSort, algorithms::comb_sort)
SORT_TEST_P(BidirectionalIteratorTest, CombSort, algorithms::comb_sort)
SORT_TEST_P(ForwardIteratorTest, CombSort, algorithms::comb_sort)

// Gnome sort test
SORT_TEST_P(RandomIteratorTest, GnomeSort, algorithms::gnome_sort)
SORT_TEST_P(BidirectionalIteratorTest, GnomeSort, algorithms::gnome_sort)

// Counting sort test
SORT_TEST_P(RandomIteratorTest, CountingSort, algorithms::counting_sort)
SORT_TEST_P(BidirectionalIteratorTest, CountingSort, algorithms::counting_sort)

// Heap sort test
SORT_TEST_P(RandomIteratorTest, HeapSort, algorithms::heap_sort)

// Insertion sort test
SORT_TEST_P(RandomIteratorTest, InsertionSort, algorithms::insertion_sort)
SORT_TEST_P(BidirectionalIteratorTest, InsertionSort, algorithms::insertion_sort)

// Intro sort test
SORT_TEST_P(RandomIteratorTest, IntroSort, algorithms::intro_sort)

// Merge sort buffered test
SORT_TEST_P(RandomIteratorTest, MergeSortBuffered, algorithms::merge_sort_buffered)
SORT_TEST_P(BidirectionalIteratorTest, MergeSortBuffered, algorithms::merge_sort_buffered)
SORT_TEST_P(ForwardIteratorTest, MergeSortBuffered, algorithms::merge_sort_buffered)

// Optimized bubble sort test
SORT_TEST_P(RandomIteratorTest, OptimizedBubbleSort, algorithms::optimized_bubble_sort)
SORT_TEST_P(BidirectionalIteratorTest, OptimizedBubbleSort, algorithms::optimized_bubble_sort)
SORT_TEST_P(ForwardIteratorTest, OptimizedBubbleSort, algorithms::optimized_bubble_sort)

// Patience sort test
SORT_TEST_P(RandomIteratorTest, PatienceSort, algorithms::patience_sort)

// Quick sort hoare test
SORT_TEST_P(RandomIteratorTest, QuickSortHoare, algorithms::quick_sort_hoare)
SORT_TEST_P(BidirectionalIteratorTest, QuickSortHoare, algorithms::quick_sort_hoare)

// Quick sort lomuto test
SORT_TEST_P(RandomIteratorTest, QuickSortLomuto, algorithms::quick_sort_lomuto)
SORT_TEST_P(BidirectionalIteratorTest, QuickSortLomuto, algorithms::quick_sort_lomuto)

// Radix sort test
SORT_TEST_P(RandomIteratorTest, RadixSort, algorithms::radix_sort)
SORT_TEST_P(BidirectionalIteratorTest, RadixSort, algorithms::radix_sort)

// Selection sort test
SORT_TEST_P(RandomIteratorTest, SelectionSort, algorithms::selection_sort)
SORT_TEST_P(BidirectionalIteratorTest, SelectionSort, algorithms::selection_sort)
SORT_TEST_P(ForwardIteratorTest, SelectionSort, algorithms::selection_sort)

// Shaker sort test
SORT_TEST_P(RandomIteratorTest, ShakerSort, algorithms::shaker_sort)
SORT_TEST_P(BidirectionalIteratorTest, ShakerSort, algorithms::shaker_sort)

// Shell sort test
SORT_TEST_P(RandomIteratorTest, ShellSort, algorithms::shell_sort)
SORT_TEST_P(BidirectionalIteratorTest, ShellSort, algorithms::shell_sort)

// Smooth sort test
SORT_TEST_P(RandomIteratorTest, SmoothSort, algorithms::smooth_sort)

// Stooge sort test
SORT_TEST_P(RandomIteratorTest, StoogeSort, algorithms::stooge_sort)
SORT_TEST_P(BidirectionalIteratorTest, StoogeSort, algorithms::stooge_sort)

// Tim sort test
SORT_TEST_P(RandomIteratorTest, TimSort, algorithms::tim_sort)
SORT_TEST_P(BidirectionalIteratorTest, TimSort, algorithms::tim_sort)

// Tree sort test
SORT_TEST_P(RandomIteratorTest, TreeSort, algorithms::tree_sort)
SORT_TEST_P(BidirectionalIteratorTest, TreeSort, algorithms::tree_sort)
SORT_TEST_P(ForwardIteratorTest, TreeSort, algorithms::tree_sort)

const static std::vector<int> LengthParam { 0, 1, 2, 31, 512, 1023 };

INSTANTIATE_TEST_SUITE_P(SortTest, RandomIteratorTest, ::testing::ValuesIn(LengthParam));
INSTANTIATE_TEST_SUITE_P(SortTest, BidirectionalIteratorTest, ::testing::ValuesIn(LengthParam));
INSTANTIATE_TEST_SUITE_P(SortTest, ForwardIteratorTest, ::testing::ValuesIn(LengthParam));

INSTANTIATE_TEST_SUITE_P(SortTest, RandomIteratorTestFloat, ::testing::ValuesIn(LengthParam));
INSTANTIATE_TEST_SUITE_P(SortTest, BidirectionalIteratorTestFloat, ::testing::ValuesIn(LengthParam));
INSTANTIATE_TEST_SUITE_P(SortTest, ForwardIteratorTestFloat, ::testing::ValuesIn(LengthParam));
