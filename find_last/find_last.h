#pragma once

template <class Iterator, class T>
Iterator FindLast(Iterator first, Iterator last, const T& val) {
    Iterator result = last;
    while (last != first) {
        --last;
        if (*last == val) {
            result = last;
            break;
        }
    }
    return result;
}
