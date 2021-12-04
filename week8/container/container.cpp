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

#include "container.h"

// Container
void fill_container(container &c) {
    for (size_t i = 0; i < c.size(); ++i) {
        c[i] = i + 1;
    }
}

double sum_container(const container &c) {
    double result = 0;
    for (size_t i = 0; i < c.size(); ++i) {
        result += c[i];
    }
    return result;
}

// Vector
vec::vec(size_t size) : data(std::vector<double>(size)) {}
double &vec::operator[](size_t idx) { return data[idx]; }
const double &vec::operator[](size_t idx) const { return data[idx]; }
size_t vec::size() const { return data.size(); }

// List
lst::lst(size_t size) : data(std::list<double>(size)) {}
size_t lst::size() const { return data.size(); }
double &lst::operator[](size_t idx) {
    auto li = data.begin();  // list iterator
    std::advance(li, idx);
    return *li;
}
const double &lst::operator[](size_t idx) const {
    auto li = data.begin();  // list iterator
    std::advance(li, idx);
    return *li;
}
