#include "range.h"

std::vector<int> Range(int from, int to, int step) {
    std::vector<int> res;
    if (step > 0) {
        for (int i = from; i < to; i += step) {
            res.push_back(i);
        }
    } else if (step < 0) {
        for (int i = from; i > to; i += step) {
            res.push_back(i);
        }
    }
    return res;
}