#include <functional>

template <class Iterator, class Comparator = std::less<typename std::iterator_traits<Iterator>::value_type>>
void Sort(Iterator begin, Iterator end, Comparator comparator = Comparator()) {
    for (auto i = begin; i != end; ++i) {
        for (auto j = std::next(i); j != end; ++j) {
            if (comparator(*j, *i)) {
                std::swap(*i, *j);
            }
        }
    }
}
