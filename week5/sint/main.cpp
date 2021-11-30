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

#include <exception>
#include <iostream>
#include <limits>

#include "sint.h"

int main() {
    // You are of course free to extend these tests!

    // just a small test
    sint a = 1;
    std::cout << sizeof(a) << std::endl;
    sint b(41);
    sint c = a + b;
    std::cout << "c: " << c << '\n';
    c++;
    std::cout << "c++: " << c << '\n';
    c--;
    std::cout << "c--: " << c << '\n';
    ++c;
    std::cout << "++c: " << c << '\n';
    --c;
    std::cout << "--c: " << c << '\n';

    // setup some values
    sint max = std::numeric_limits<int>::max();
    sint min = std::numeric_limits<int>::min();
    sint result;

    // test operator+
    result = max + sint(10);
    std::cout << result << '\n';
    result = min + sint(-10);
    std::cout << result << '\n';

    // test operator-
    result = min - sint(10);
    std::cout << result << '\n';
    result = max - sint(-10);
    std::cout << result << '\n';

    // test operator*
    result = max * sint(2);
    std::cout << result << '\n';
    result = min * sint(2);
    std::cout << result << '\n';

    // test operator/
    result = sint(42) / sint(0);
    std::cout << result << '\n';

    return 0;
}
