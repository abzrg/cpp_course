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

#ifndef SINT_H_
#define SINT_H_

#include <exception>
#include <iostream>
#include <limits>
#include <string>

class sint {
private:
    int value;

public:
    sint();
    sint(int i);
    ~sint();
    sint(const sint &s);
    sint &operator=(const sint &s);
    sint(sint &&s);
    sint &operator=(sint &&s);
    int getUnderlyingValue() const noexcept;
    friend sint operator+(sint lhs, sint rhs);
    friend sint operator-(sint lhs, sint rhs);
    friend sint operator*(sint lhs, sint rhs);
    friend sint operator/(sint lhs, sint rhs);
    sint &operator++();    // prefix ++: no parameter, returns a reference
    sint operator++(int);  // postfix ++: dummy parameter, returns a value
    sint &operator--();    // prefix ++: no parameter, returns a reference
    sint operator--(int);  // postfix ++: dummy parameter, returns a value
    friend std::ostream &operator<<(std::ostream &os, const sint &s);
};

#endif
