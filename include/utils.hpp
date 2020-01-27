#pragma once

#include <chrono>
#include <random>
#include <type_traits>


template<typename T>
T random(T min, T max) {
    static std::mt19937 gen(
            std::chrono::high_resolution_clock::now().time_since_epoch().count());
    if constexpr (std::is_floating_point<T>::value) {
        return std::uniform_real_distribution<T>(min, max)(gen);
    } else {
        return std::uniform_int_distribution<T>(min, max)(gen);
    }
}
