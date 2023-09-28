#include "password.h"

#include <algorithm>
#include <string>

bool ValidatePassword(const std::string& password) {
    const int min_password_length = 8;
    const int max_password_length = 14;
    const int min_ackii_table = 33;
    const int max_ackii_table = 126;
    if (password.length() < min_password_length || password.length() > max_password_length) {
        return false;
    }

    bool has_uppercase = false;
    bool has_lowercase = false;
    bool has_digit = false;
    bool has_other = false;
    for (char c : password) {
        if (c < min_ackii_table || c > max_ackii_table) {
            return false;
        }
        if (std::isupper(c)) {
            has_uppercase = true;
        } else if (std::islower(c)) {
            has_lowercase = true;
        } else if (std::isdigit(c)) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }

    int num_classes = has_uppercase + has_lowercase + has_digit + has_other;
    return num_classes >= 3;
}