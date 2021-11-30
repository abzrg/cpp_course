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

#include "sint.h"

// -- Constructors / Destructors

sint::sint() : value(0) {}
sint::sint(int i) : value(i) {}
sint::~sint() = default;

// -- Copy/Move ctors and assinment operators

sint::sint(const sint &s) = default;

sint &sint::operator=(const sint &s) = default;

sint::sint(sint &&s) = default;

sint &sint::operator=(sint &&s) = default;

// -- Methods

int sint::getUnderlyingValue() const noexcept { return value; }

// -- Operators

sint operator+(sint lhs, sint rhs) {
    sint result;
    if (__builtin_add_overflow(lhs.value, rhs.value, &result.value))
        // In the case of addition only overflow would make sense
        throw std::overflow_error("ERROR: Integer overflow; result: " +
                                  std::to_string(result.value));
    return result;
}

sint operator-(sint lhs, sint rhs) {
    sint result;
    if (__builtin_sub_overflow(lhs.value, rhs.value, &result.value))
        // In the case of addition only underflow would make sense
        throw std::underflow_error("ERROR: Integer underflow; result: " +
                                   std::to_string(result.value));
    return result;
}

sint operator*(sint lhs, sint rhs) {
    sint result;
    if (__builtin_mul_overflow(lhs.value, rhs.value, &result.value))
        // In the case of addition only overflow would make sense
        throw std::overflow_error("ERROR: Integer overflow; result: " +
                                  std::to_string(result.value));
    return result;
}

sint operator/(sint lhs, sint rhs) {
    sint result;
    if (rhs.value == 0)
        // For the case of division by zero throw an logical error
        throw std::logic_error("ERROR: Division by zero");
    return lhs.value / rhs.value;
}

sint &sint::operator++() {
    if (__builtin_add_overflow(value, 1, &value))
        throw std::overflow_error("ERROR: Integer overflow; result: " +
                                  std::to_string(value));
    return *this;
}

sint sint::operator++(int) {
    if (__builtin_add_overflow(value, 1, &value))
        throw std::overflow_error("ERROR: Integer overflow; result: " +
                                  std::to_string(value));
    return *this;
}

sint &sint::operator--() {
    if (__builtin_sub_overflow(value, 1, &value))
        throw std::underflow_error("ERROR: Integer underflow; result: " +
                                   std::to_string(value));

    return *this;
}

sint sint::operator--(int) {
    if (__builtin_sub_overflow(value, 1, &value))
        throw std::underflow_error("ERROR: Integer underflow; result: " +
                                   std::to_string(value));
    return *this;
}

std::ostream &operator<<(std::ostream &os, const sint &s) {
    return os << s.value;
}

// Refs:
// ---------------------------

// 1. Overloading increment and decrement operators:
//      https://docs.microsoft.com/en-us/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=msvc-160

// 2. Why use logical_error exception for divide by zero:
//      https://stackoverflow.com/a/6121690/13041067

// 3. How detect integer overflow:
//      https://stackoverflow.com/a/20956705/13041067

// 4. Overload operator must be a unary or binary operator error:
//      https://stackoverflow.com/a/13554338/13041067

// 5. Why we use ; after } in a class declaration (also read the comments under
// the answer)
//      https://stackoverflow.com/a/19164814/13041067
//      https://web.archive.org/web/20100906085102/http://cpptalk.net/confused-about-the-meaning-of-the-semicolon-vt11965.html

// 6. Use of ; after class name (forward declaration--why compilers cannot
// lookup, so if they cannot find it in the compilation unit, it does not exits)
//      https://stackoverflow.com/a/24835588/13041067
//      https://stackoverflow.com/a/1410632/13041067 -- diffrence between the
//      declaration and definition https://stackoverflow.com/a/4757718/13041067
//      -- forward declaration
//      https://stackoverflow.com/questions/9119236/c-class-forward-declaration

// 7. How and where compiler stores member functions?
//      https://stackoverflow.com/questions/15572411/where-are-member-functions-stored-for-an-object
