#ifndef BUBBLE_SORT_
#define BUBBLE_SORT_

#include <algorithm>  // use: swap (https://en.cppreference.com/w/cpp/algorithm/swap)
#include <iostream>
#include <iterator>  // use: next (https://en.cppreference.com/w/cpp/iterator/next)
#include <vector>

void bubble_sort(std::vector<int> &v);

void bubble_sort(std::vector<int> &v, size_t from, size_t to);

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v);

#endif  // BUBBLE_SORT
