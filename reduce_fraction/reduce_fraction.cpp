#include "reduce_fraction.h"

int64_t Gcd(int64_t first, int64_t second) {
    if (second == 0) {
        return first;
    }
    return Gcd(second, first % second);
}
int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t divisor = Gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
    return numerator + denominator;
}
