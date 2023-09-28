#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    auto left = 0;
    auto right = str.length() - 1;
    if (str.empty()) {
        return true;
    }
    while ((left - right) / 2 != 0) {
        if (str[right] == ' ') {
            --right;
            continue;
        }
        if (str[left] == ' ') {
            ++left;
            continue;
        }
        if (str[left] != str[right]) {
            return false;
        }
        ++left;
        --right;
    }
    return true;
}