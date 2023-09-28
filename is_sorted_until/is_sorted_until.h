#pragma once

template <typename T>
T IsSortedUntil(T begin, T end) {
    T iter_next = ++begin;
    for (auto iter = iter_next; iter < end; ++iter) {
        if (*iter < *(iter - 1)) {
            return iter;
        }
    }
    return end;
}