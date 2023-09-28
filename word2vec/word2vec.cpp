#include "word2vec.h"

#include <numeric>
#include <vector>

std::vector<std::string> FindClosestWords(const std::vector<std::string>& words,
                                          const std::vector<std::vector<int>>& vectors) {
    if (words.size() <= 1) {
        return std::vector<std::string>(0);
    }
    std::vector<int64_t> sk(vectors.size() - 1);
    for (auto i = 1; i < vectors.size(); ++i) {
        sk[i - 1] =
            std::inner_product(vectors[0].begin(), vectors[0].end(), vectors[i].begin(), static_cast<int64_t>(0));
    }
    int64_t maximum = *std::max_element(sk.begin(), sk.end());
    std::vector<std::string> answer(std::count(sk.begin(), sk.end(), maximum));
    int j = 0;
    for (auto i = 0; i < sk.size(); ++i) {
        if (sk[i] == maximum) {
            ++j;
            answer[j - 1] = words[i + 1];
        }
    }
    return answer;
}