#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T, typename U>
T Remove(T begin, T end, U value) {
    auto iter = begin;
    for (auto it = begin; it < end; ++it) {
        if (*it != value) {
            *iter = std::move(*it);
            ++iter;
        }
    }
    return iter;
}
