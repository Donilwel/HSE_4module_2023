#include "sum_digits.h"

int64_t SumOfDigits(int64_t number) {
    int64_t sum = 0;
    const int tan = 10;
    while (number > 0) {
        sum += number % tan;
        number /= tan;
    }
    return sum;
}
