#include "../include/tools.hpp"
#include <sorter>
#include <functional>

#define STABLE_SORT_TEST_BODY(Sort, Container, Compare)                                                     \
    auto First = Container.begin();                                                                         \
    auto Last = Container.end();                                                                            \
    auto Pred = Compare;                                                                                    \
    auto CmpFirst = [&Pred](const auto& Lhs, const auto& Rhs) { return Pred(Lhs.first, Rhs.first); };       \
    std::invoke(Sort, First, Last, CmpFirst);                                                               \
    ASSERT_TRUE(std::is_sorted(First, Last, CmpFirst));                                                     \
    auto CmpSecond = [&Pred](const auto& Lhs, const auto& Rhs) { return Pred(Lhs.second, Rhs.second); };    \
    std::invoke(Sort, Container, CmpSecond);                                                                \
    ASSERT_TRUE(std::is_sorted(First, Last, CmpSecond));                                                    \
    ASSERT_EQ(this->IsStabilitySorted(Pred), static_cast<bool>(algorithms::is_stable_v<decltype(Sort)>))

template<class T1, class T2>
class RandomGenerator<std::pair<T1, T2>> {
public:
    using generator_first = RandomGenerator<T1>;
    using generator_second = RandomGenerator<T2>;

    RandomGenerator() = default;

    constexpr auto operator()() const {
        generator_first gen1;
        generator_second gen2;
        return std::make_pair(gen1(), gen2());
    }
};

template<class Sorter>
class TypesStableSortTest : public TypeRandomSequence<std::vector<std::pair<int, float>>> {
public:
    using sorter_type = Sorter;
    using first_type = typename value_type::first_type;
    using second_type = typename value_type::second_type;

    static constexpr size_t MIN_REPEATE = 1;
    static constexpr size_t MAX_REPEATE = 7;

    void SetUp() override {
        this->Fill(SIZE);

        std::mt19937 gen_repeat(std::rand());
        std::uniform_int_distribution<> range_repeate(MIN_REPEATE, MAX_REPEATE);

        for (auto iter = container.begin(); iter != container.end(); ) {
            auto count_repeat = range_repeate(gen_repeat);
            const second_type repeat_item = iter->second;
            for (; iter != container.end() && count_repeat > 0; ++iter, --count_repeat)
                iter->second = repeat_item;
        }
    }

    template<class Pred = std::less<>>
    bool IsStabilitySorted(Pred pred = Pred()) const {
        for (auto current = container.cbegin() + 1; current != container.cend(); ++current) {
            auto prev = std::prev(current);
            if (prev->second == current->second && !(prev->first == current->first)) {
                if(!pred(prev->first, current->first))
                     return false;
            } 
        }
        return true;
    }

protected:
    sorter_type sort;
};

TYPED_TEST_SUITE_P(TypesStableSortTest);

TYPED_TEST_P(TypesStableSortTest, LESS) {
    STABLE_SORT_TEST_BODY(this->sort, this->container, std::less<>());
}

TYPED_TEST_P(TypesStableSortTest, GREATER) {
    STABLE_SORT_TEST_BODY(this->sort, this->container, std::greater<>());
}

REGISTER_TYPED_TEST_SUITE_P(TypesStableSortTest, LESS, GREATER);

using Types = ::testing::Types<
    algorithms::binary_insertion_sorter,
    algorithms::bubble_sorter,
    algorithms::optimized_bubble_sorter,
    algorithms::comb_sorter,
    algorithms::gnome_sorter,
    algorithms::heap_sorter,
    algorithms::insertion_sorter,
    algorithms::insertion_sorter,
    algorithms::buffered_merge_sorter,
    algorithms::patience_sorter,
    algorithms::quick_sorter,
    algorithms::quick_sorter_lomuto,
    algorithms::selection_sorter,
    algorithms::shaker_sorter,
    algorithms::shell_sorter,
    algorithms::smooth_sorter,
    algorithms::stooge_sorter,
    algorithms::tim_sorter,
    algorithms::tree_sorter
>;

INSTANTIATE_TYPED_TEST_SUITE_P(StableTest, TypesStableSortTest, Types);