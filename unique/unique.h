#pragma once

template <typename T>
T Unique(T begin, T end) {
    if (begin == end) {
        return end;
    }
    T last_unique = begin;
    ++begin;
    while (begin != end) {
        if (*last_unique != *begin) {
            ++last_unique;
            *last_unique = *begin;
        }
        ++begin;
    }
    ++last_unique;
    return last_unique;
}