#include "tests_checking.h"

#include <string>
#include <vector>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::vector<std::string> stack;

    for (auto it = student_actions.begin(); it < student_actions.end(); ++it) {
        const auto& action = *it;
        if (!(action.side == Side::Top)) {
            stack.push_back(action.name);
        } else {
            stack.insert(stack.begin(), action.name);
        }
    }

    std::vector<std::string> result;
    for (auto it = 0; it < queries.size(); ++it) {
        auto query = queries[it];
        auto query_before = query - 1;
        result.push_back(stack[query_before]);
    }

    return result;
}
