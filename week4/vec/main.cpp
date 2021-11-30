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

#include <initializer_list>
#include <iostream>
#include <utility>

#include "vec.h"

/// In main we will test all of the above functions and see if they are working
/// correctly.
int main() {
    // Please de-comment the following lines as you have implemented the
    // necessary functionalities. Hint: It is probably a good idea to start
    // implementing the constructors and operator<< so you can see what is going
    // on!

    vec v(10);  // call to the first constructor
    std::cout << v << '\n';
    vec w(8, 42.123);  // call to the second constructor
    std::cout << w << '\n';
    vec x = {1, 2, 3};  // call to the third constructor
    std::cout << "x: " << x << '\n';

    vec z(x);  // call to copy constructor
    std::cout << z << '\n';
    vec m = z;  // call to copy constructor
    std::cout << m << '\n';
    z = w;  // call to copy assignment operator
    std::cout << z << '\n';

    vec v1 = std::move(x);  // call to move assign -> move constructor
    std::cout << "v1: " << v1 << '\n';  // call to operator<<
    // do not use x after this statement
    vec v2 = {4, 5, 6};  // call to the third constructor
    vec v3 = {7, 8, 9};  // call to the third constructor
    vec v4 = v2;         // call to copy assign -> copy constructor

    std::cout << v4 << '\n';                              // call to operator<<
    v4[0] = 11;                                           // call to operator[]
    v4[1] = 12;                                           // call to operator[]
    std::cout << v4 << '\n';                              // call to operator<<
    std::cout << "size: " << v4.size() << '\n';           // call to size()
    std::cout << "add v1 and v2: " << (v1 + v2) << '\n';  // call to operator+
    std::cout << "sub v1 and v2: " << (v1 - v2) << '\n';  // call to operator-
    // call to operator*
    std::cout << "scalar product v1 and v2: " << (v1 * v2) << '\n';
    // call to the other operator*
    std::cout << "v1 times 2: " << (v1 * 2) << '\n';
    const vec v5(3, 42);  // call to second constructor, note v5 is const!
    // this calls the const version of operator[], since v5 is const
    std::cout << v5[0] << '\n';
    // this calls the const version of operator[], since v5 is const
    std::cout << v5[2] << '\n';
    // At this point the destructors for all vec variables are called, because
    // all these variables go out of scope at the end of this function.
    return 0;
}
