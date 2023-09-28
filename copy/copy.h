#pragma once

template <typename T, typename U>
U Copy(T src_begin, T src_end, U dest) {
    for (auto it = src_begin; it < src_end; ++it) {
        *dest = *it;
        ++dest;
    }
    return dest;
}

template <typename T, typename U>
U CopyBackward(T src_begin, T src_end, U dest) {
    while (src_begin != src_end) {
        auto before_elem = --src_end;
        auto before_elem_dest = --dest;
        *before_elem_dest = *before_elem;
    }
    return dest;
}
