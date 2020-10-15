#pragma once
#include <utils>

namespace algorithms {
    namespace policy {
        template<class Sorter>
		struct iterator_interface {
			template<class Iterator, class Pred = std::less<>>
			void operator()(Iterator First, Iterator Last, Pred Compare = Pred()) {
				return static_cast<Sorter*>(this)->execute(First, Last, Compare);
			}

			template<class Iterator, class Pred = std::less<>>
			void operator()(Iterator First, const size_t Count, Pred Compare = Pred()) {
				return this->operator()(First, std::next(First, Count), Compare);
			}
		};

		template<class Sorter>
		struct container_interface {
			template<class Cont, class Pred = std::less<>>
			void operator()(Cont& Container, Pred Compare = Pred()) const {
				return static_cast<const Sorter*>(this)->execute(std::begin(Container), std::end(Container), Compare);
			}

			template<class Cont, class Pred = std::less<>>
			void operator()(Cont& Container, const size_t Count, Pred Compare = Pred()) const {
				auto First = std::begin(Container);
				auto Last = std::next(First, Count);
				return static_cast<const Sorter*>(this)->execute(First, Last, Compare);
			}
		};

		template<class Sorter>
		struct full_interface {
			template<class Iterator, class Pred = std::less<>, class = enable_if_iterator<Iterator>>
			void operator()(Iterator First, Iterator Last, Pred Compare = Pred()) {
				return static_cast<Sorter*>(this)->execute(First, Last, Compare);
			}

			template<class Iterator, class Pred = std::less<>, class = enable_if_iterator<Iterator>>
			void operator()(Iterator First, const size_t Count, Pred Compare = Pred()) {
				return this->operator()(First, std::next(First, Count), Compare);
			}

			template<class Cont, class Pred = std::less<>, class = disable_if_iterator<Cont>>
			void operator()(Cont& Container, Pred Compare = Pred()) {
				return this->operator()(std::begin(Container), std::end(Container), Compare);
			}

			template<class Cont, class Pred = std::less<>, class = disable_if_iterator<Cont>>
			void operator()(Cont& Container, const size_t Count, Pred Compare = Pred()) {
				auto First = std::begin(Container);
				auto Last = std::next(First, Count);
				return this->operator()(First, Last, Compare);
			}
		};

		struct parallel_execute {
			static constexpr bool parallel = true;
		};

		struct sequential_execute {
			static constexpr bool parallel = false;
		};
    } // namespace policy
} // namespace algorithms