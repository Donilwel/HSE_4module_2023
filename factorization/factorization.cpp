#include "factorization.h"

#include <utility>
#include <vector>

#include "cmath"

std::vector<std::pair<int64_t, int>> Factorize(int64_t n) {
    std::vector<std::pair<int64_t, int>> result;
    for (int64_t i = 2; i <= static_cast<int64_t>(std::sqrt(n)); ++i) {
        int counter = 0;
        while (n % i == 0) {
            ++counter;
            n /= i;
        }
        if (counter > 0) {
            result.emplace_back(i, counter);
        }
    }
    if (n > 1) {
        result.emplace_back(n, 1);
    }
    return result;
}