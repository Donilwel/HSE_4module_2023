#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t first = 0;
    int64_t second = 1;
    for (int i = 2; i <= n; ++i) {
        int64_t cut = first + second;
        first = second;
        second = cut;
    }
    return n == 0 ? first : second;
}
