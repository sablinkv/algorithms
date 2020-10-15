#pragma once
#include <gtest/gtest.h>
#include <random>
#include <algorithm>
#include <chrono>

template<class T>
class RandomGenerator {
public:
    using value_type = T;
    static_assert(std::is_arithmetic_v<value_type>, "Template type must be arithmetic type.");

    using distribution_type = std::conditional_t<
        std::is_floating_point_v<value_type>,
        std::uniform_real_distribution<>,
        std::uniform_int_distribution<>
    >;
    using param_type = typename distribution_type::param_type;

    constexpr RandomGenerator() {
        if constexpr(std::is_floating_point_v<T>) // for bucket sort
            _param = param_type(0, 1);
        if constexpr(std::is_integral_v<T>) // other sort
            _param = param_type(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
    }

    auto operator()() const {
        std::mt19937 gen(std::rand()); 
        distribution_type dist(_param);   
        return static_cast<value_type>(dist(gen));
    }

private:
    param_type _param;
};

template<class Container>
class TypeRandomSequence : public ::testing::Test {
public:
    using container_type = Container;
    using value_type = typename container_type::value_type;

    static constexpr size_t SIZE = 128;
    
    virtual void SetUp() override {
        Fill(SIZE);
    }

    virtual ~TypeRandomSequence() {}

protected:
    void Fill(const size_t size) {
        container.resize(size);
        std::generate(std::begin(container), std::end(container), RandomGenerator<value_type>());
    }

    container_type container;
};
