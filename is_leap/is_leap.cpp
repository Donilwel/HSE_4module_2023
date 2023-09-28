#include "is_leap.h"

bool IsLeap(int year) {
    const int first = 100;
    const int second = 400;
    if ((year % 4 == 0 && year % first != 0) || year % second == 0) {
        return true;
    }
    return false;
}
