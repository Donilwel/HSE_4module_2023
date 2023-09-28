#include "provinces.h"

#include <queue>

int64_t CountPassports(const std::vector<int>& provinces) {
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> provinces_new;
    for (int i = 0; i < provinces.size(); ++i) {
        provinces_new.push(provinces[i]);
    }
    int64_t answer = 0;
    while (provinces_new.size() > 1) {
        auto first = provinces_new.top();
        provinces_new.pop();
        auto second = provinces_new.top();
        provinces_new.pop();
        auto new_province = first + second;
        answer += new_province;
        provinces_new.push(new_province);
    }
    return answer;
}
