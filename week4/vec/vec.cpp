#include "vec.h"

// --- Constructors

vec::vec(size_t size) : elements(size), data(new double[size]) {}

vec::vec(size_t size, double ival) : vec(size) {
    for (size_t i = 0; i < size; ++i) {
        data[i] = ival;
    }
}

// (idea from: https://www.learncpp.com/cpp-tutorial/stdinitializer_list/)
vec::vec(std::initializer_list<double> ilist)
    : vec(ilist.size()) {  // or std::size(ilist)
    // size_t i = 0;
    // for (auto item : ilist) {
    //     data[i] = item;
    //     ++i;
    // }

    // My implementation
    for (size_t i = 0; i < ilist.size(); ++i) {
        data[i] = ilist.begin()[i];
    }
}

// --- Destructor

vec::~vec() {
    delete[] data;
    // we don't need to set data to null or elements to 0 here, since the object
    // will be destroyed immediately after this function anyway
    // (source: https://www.learncpp.com/cpp-tutorial/stdinitializer_list/)
}

// --- Copy/Move constructor/assignment operator

vec::vec(const vec &v) : elements(v.elements), data(new double[elements]) {
    for (size_t i = 0; i < elements; ++i) data[i] = v.data[i];
}

vec &vec::operator=(const vec &v) {
    // If you are copying yourself
    if (this == &v) return *this;

    elements = v.elements;
    // Free the current resources data is pointing at
    // Do this before loosing the handle in the next line
    delete[] data;
    data = new double[elements];
    for (size_t i = 0; i < elements; ++i) data[i] = v.data[i];
    return *this;
}

vec::vec(vec &&v) : elements(v.elements), data(v.data) { v.data = nullptr; }

vec &vec::operator=(vec &&v) {
    // If you are copying yourself
    if (this == &v) return *this;

    // First delete what ultimately will be thrown away
    delete[] data;
    data = v.data;
    v.data = nullptr;
    return *this;
}

// --- Other methods

size_t vec::size() const { return elements; }

// --- Other Operators

double &vec::operator[](size_t idx) { return data[idx]; }

const double &vec::operator[](size_t idx) const { return data[idx]; }

std::ostream &operator<<(std::ostream &os, const vec &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i] << " ";
    }
    return os;
}

vec operator+(vec lhs, const vec &rhs) {
    // Check two vector are of the same size. If not the same, return [-1]
    if (lhs.size() != rhs.size()) return vec(1, -1.0);

    for (size_t i = 0; i < lhs.elements; ++i) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

vec operator-(vec lhs, const vec &rhs) {
    // Check two vector are of the same size. If not the same, return [-1]
    if (lhs.size() != rhs.size()) return vec(1, -1.0);

    for (size_t i = 0; i < lhs.elements; ++i) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

vec operator*(vec lhs, double scale) {
    for (size_t i = 0; i < lhs.elements; ++i) {
        lhs[i] *= scale;
    }
    return lhs;
}

double operator*(const vec &lhs, const vec &rhs) {
    // Check two vector are of the same size
    if (lhs.size() != rhs.size()) return -1.0;

    double product = 0;
    for (size_t i = 0; i < lhs.elements; ++i) {
        product += lhs[i] * rhs[i];
    }
    return product;
}
