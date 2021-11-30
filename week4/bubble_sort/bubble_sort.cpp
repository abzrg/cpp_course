#include "bubble_sort.h"

// https://www.delftstack.com/howto/cpp/bubble-sort-in-cpp/

// auto == std::vector<int>::iterator

void bubble_sort(std::vector<int> &v) {
    for (size_t i = 0, size = v.size(); i < size - 1; ++i) {
        for (size_t j = 1; j < size - i; ++j)
            if (v.at(j) < v.at(j - 1)) std::swap(v.at(j), v.at(j - 1));
    }
}

void bubble_sort(std::vector<int> &v, size_t from, size_t to) {
    // Calculate the size of vector only once
    size_t size = v.size();

    // Check for the correct vales of 'from' and 'to'
    if (from < 0 || to > size) {
        std::cout << "ERROR: Out of Bound!\n";
        return;
    }

    for (size_t i = from; i < to - 1; ++i) {
        for (size_t j = 1; j < to - i; ++j)
            if (v.at(j) < v.at(j - 1)) std::swap(v.at(j), v.at(j - 1));
    }
}

// https://www.cplusplus.com/reference/algorithm/
// https://en.cppreference.com/w/cpp/algorithm
std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(os, " "));
    return os;
}
