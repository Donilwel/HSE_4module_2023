#pragma once
#include "iostream"

template <typename Iterator>
void Reverse(Iterator begin, Iterator end) {
    while (begin != end && begin != --end) {
        std::iter_swap(begin++, end);
    }
}

template <typename Iterator>
void Rotate(Iterator begin, Iterator mid, Iterator end) {
    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}
