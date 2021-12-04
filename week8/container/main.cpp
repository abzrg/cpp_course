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

#include "container.h"

int main() {
    vec v(10);
    lst l(10);

    fill_container(v);
    fill_container(l);

    int sum = 0;
    sum = sum_container(v);
    std::cout << sum << '\n';
    sum = sum_container(l);
    std::cout << sum << '\n';

    return 0;
}
