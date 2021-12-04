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

#ifndef MEAN_TEMPLATE_ERROR_H_
#define MEAN_TEMPLATE_ERROR_H_

#include <iostream>

// Base
template <class T>
class base {
protected:
    T base_value;

public:
    base(T t);
};

// Dervied
template <class T>
class derived : public base<T> {
private:
    T derived_value;

public:
    derived(T t, T u);
    void printValues();
};

// Defining template functions in a cpp file (only to know how)
// source: https://stackoverflow.com/a/26816994/13041067
#define MEAN_TEMPLATE_ERROR_CPP_
#include "mean_template_error.cpp"

#endif
