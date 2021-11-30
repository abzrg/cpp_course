//===----------------------------------------------------------------------===//
//
// Philipp Schubert
//
//    Copyright (c) 2017 - 2021
//    Secure Software Engineering Group
//    Heinz Nixdorf Institute
//    Paderborn University
//    philipp.schubert@upb.de
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <vector>

#include "bubble_sort.h"

int main() {
    std::vector<int> v = {1, 5, 6, 23, 7, 8, 9, 21, 12, 4};
    std::cout << "unsorted: ";
    std::cout << v << '\n';
    bubble_sort(v);
    std::cout << "sorted: ";
    std::cout << v << '\n';

    std::vector<int> w = {1, 5, 6, 23, 7, 8, 9, 21, 12, 4};
    std::cout << "unsorted: ";
    std::cout << w << '\n';
    bubble_sort(w, 0, 5);
    std::cout << "partially sorted: ";
    std::cout << w << '\n';

    return 0;
}
