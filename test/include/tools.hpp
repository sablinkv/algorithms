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

    constexpr value_type operator()() const {
        const auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
        std::mt19937_64 gen(seed); 
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
    using generator_type = RandomGenerator<value_type>;

    static constexpr size_t SIZE = 128;
    
    virtual void SetUp() override {
        Fill(SIZE);
    }

    virtual ~TypeRandomSequence() {}

protected:
    void Fill(const size_t size) {
        generator_type gen;
        container.resize(size);
        std::generate(std::begin(container), std::end(container), gen);
    }

    container_type container;
};

template<class Container>
class ParamRandomSequence : public TypeRandomSequence<Container>, public ::testing::WithParamInterface<int> {
public:
    virtual void SetUp() override {
        const auto lenght = GetParam();
        this->Fill(lenght);
    }

    virtual ~ParamRandomSequence() {}
};