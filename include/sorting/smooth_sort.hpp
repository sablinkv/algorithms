#pragma once
#include <utils>
#include <search>
#include <array>
#include <stdexcept>

namespace algorithms {
    class LeonardoSequence {
        constexpr void fill() {
            auto Prev = m_Sequence.cbegin();
            auto Current = Prev + 1;
            auto Place = m_Sequence.begin() + 2;
            auto Last = m_Sequence.end();
            do {
                const auto Next = *Current + *Prev + 1;
                *Place = Next;
                Prev = Current;
                Current = Place;
            } while (++Place != Last);
        }

    public:
        using container_type = std::array<size_t, 46>;
        using const_iterator = typename container_type::const_iterator;

        explicit LeonardoSequence() {
            fill();
        }

        auto at(const size_t index) const {
            return m_Sequence.at(index);
        }

        const_iterator near(const size_t value) const noexcept {
            auto Iter = algorithms::lower_bound(std::cbegin(m_Sequence), std::cend(m_Sequence), value);
            if (*Iter != value)
                return std::prev(Iter);
            return Iter;
        }

        const_iterator cbegin() const noexcept {
            return m_Sequence.cbegin();
        }

        const_iterator cend() const noexcept {
            return m_Sequence.cend();
        }

    private:
        container_type m_Sequence{ 1, 1 };
    };

    namespace detail {
        using Sequence_iterator = typename LeonardoSequence::const_iterator;

        template<class Random_iterator, class Binary_predicate>
        void Heapify_subheap(Random_iterator First, Random_iterator Last, Sequence_iterator Leo, Binary_predicate Compare)
        {
            if (Last - First < 2)
                return;
            
            auto NextLeo = Leo;
            auto Left = First + *(Leo - 1) - 1;
            auto Right = Last - 1;
            auto Top = Last;
            // Left subheap
            if (Compare(*Top, *Left)) {
                Top = Left;
                --NextLeo;
            }
            // Right subheap
            if (Compare(*Top, *Right)) {
                Top = Right;
                First = Left + 1;
                const auto Offset = NextLeo == Leo ? 2 : 1;
                NextLeo -= Offset;
            }

            if (Top != Last) {
                std::iter_swap(Top, Last);
                if (*NextLeo > 1)
                    Heapify_subheap(First, Top, NextLeo, Compare);
            }
        }

        template<class Random_iterator, class Binary_predicate>
        void Build_subheap(Random_iterator First, Sequence_iterator Leo, Binary_predicate Compare)
        {
            if (*Leo > 3) {
                Build_subheap(First, std::prev(Leo), Compare);
                if (*Leo > 5)
                    Build_subheap(First + *std::prev(Leo), std::prev(Leo, 2), Compare);
            }
            Heapify_subheap(First, First + *Leo - 1, Leo, Compare);
        }

        template<class Random_iterator, class Binary_predicate>
        void Make_heap_pool_unchecked(Random_iterator First, Random_iterator Last, const LeonardoSequence& Sequence, Binary_predicate Compare)
        {
            while (First != Last) {
                auto Leo = Sequence.near(Last - First);
                Build_subheap(First, Leo, Compare);
                First += *Leo;
            }
        }

        template<class Random_iterator, class Binary_predicate>
        void Pop_heap_pool_unchecked(Random_iterator First, Random_iterator Last, const LeonardoSequence& Sequence, Binary_predicate Compare)
        {
            auto Top = Last - 1;
            auto Highest = Top;
            auto Leo = Sequence.cbegin();

            while (First != Top) {
                auto NearLeo = Sequence.near(Last - First);
                auto ProcessTop = First + *NearLeo - 1;

                if (ProcessTop == Top) break;

                if (Compare(*Highest, *ProcessTop)) {
                    Highest = ProcessTop;
                    Leo = NearLeo;
                }
                First += *NearLeo;
            }

            if (Highest != Top) {
                std::iter_swap(Highest, Top);
                Heapify_subheap(std::prev(Highest, *Leo - 1), Highest, Leo, Compare);
            }
        }

        template<class Random_iterator, class Binary_predicate>
        inline void Smooth_sort_unchecked(Random_iterator First, Random_iterator Last, Binary_predicate Compare)
        {
            const LeonardoSequence Sequence;
            Make_heap_pool_unchecked(First, Last, Sequence, Compare);
            while (utility::verify_range(First, Last, 1))
                Pop_heap_pool_unchecked(First, Last--, Sequence, Compare);
        }
    } // namespace detail

    /*
        Smoot sort - NOT STABLE
        Complexity:
            Worst		case - O(N lgN);
            Average		case - θ(N lgN);
            Best		case - Ω(N).
        Space:
            Add			costs - O(1).
    */
    template<class Random_iterator, class Binary_predicate = std::less<>,
        class = std::enable_if_t<is_sortable_v<Random_iterator, std::random_access_iterator_tag>>
    >void smooth_sort(Random_iterator First, Random_iterator Last, Binary_predicate Compare = Binary_predicate())
    {
        if (utility::verify_range(First, Last, 1)) {
            utility::verify_comparator(First, std::next(First), Compare);
            detail::Smooth_sort_unchecked(First, Last, Compare);
        }
    }
} // namespace algorithms