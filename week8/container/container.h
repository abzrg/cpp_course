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

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <iostream>
#include <list>
#include <vector>

class container {
public:
    virtual ~container() = default;
    virtual double &operator[](size_t idx) = 0;
    virtual const double &operator[](size_t idx) const = 0;
    virtual size_t size() const = 0;
};

void fill_container(container &c);

double sum_container(const container &c);

// Vector
class vec : public container {
public:
    vec(size_t size);
    double &operator[](size_t idx);
    const double &operator[](size_t idx) const;
    size_t size() const;
private:
    std::vector<double> data;
};

// List
// unlike arrays and vectors, we cannot just use [] to iterate over std::lists;
// instead we need to use iterators and:
// std::advance( InputIt& it, Distance n )
class lst : public container {
public:
    lst(size_t size);
    double &operator[](size_t idx);
    const double &operator[](size_t idx) const;
    size_t size() const;
private:
    std::list<double> data;
};

#endif
