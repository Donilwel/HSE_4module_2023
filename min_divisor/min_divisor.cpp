#include "min_divisor.h"

#include <cmath>

int64_t MinDivisor(int64_t number) {
    if (number == 1) {
        return 1;
    }
    if (number % 2 == 0) {
        return 2;
    }
    int64_t div = 3;
    while (static_cast<double>(div) <= std::sqrt(number)) {
        if (number % div == 0) {
            return div;
        }
        div += 2;
    }
    return number;
}