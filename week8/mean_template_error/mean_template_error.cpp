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

#ifndef MEAN_TEMPLATE_ERROR_CPP_

#include "mean_template_error.h"
// Non-template function definitions

#else

template <class T>
base<T>::base(T t) : base_value(t) {}

template <class T>
inline derived<T>::derived(T t, T u) : base<T>(u), derived_value(t) {}

template <class T>
void derived<T>::printValues() {
    // source: https://stackoverflow.com/q/4643074/13041067
    std::cout << this->base_value << '\n';
    std::cout << derived_value << '\n';
}

#endif
