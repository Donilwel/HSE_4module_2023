#include "unixpath.h"

#include <vector>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string_view> queue;

    for (int i = 0; i < 2; ++i) {
        std::string_view poss = (i == 0) ? current_working_dir : path;
        if (!poss.empty()) {
            if (poss[0] == '/') {
                queue.clear();
            }
        }

        size_t pos = 0;
        while (pos < poss.size()) {
            if (poss[pos] == '/') {
                ++pos;
                continue;
            }

            auto posit = poss.find('/', pos);
            if (posit == std::string_view::npos) {
                posit = poss.size();
            }
            auto dir = poss.substr(pos, posit - pos);

            dir == ".." ? (!queue.empty() ? queue.pop_back() : void()) : (dir != "." ? queue.push_back(dir) : void());

            pos = posit;
        }
    }

    std::string result;
    if (queue.empty()) {
        return "/";
    }
    for (int i = 0; i < queue.size(); ++i) {
        result = result + "/" + std::string(queue[i]);
    }
    return result;
}