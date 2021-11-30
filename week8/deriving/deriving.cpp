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

class base {
public:
    virtual ~base() = default;
    virtual void whoAmI() { std::cout << "I am base\n"; }
};

class derived_one : public base {
public:
    void whoAmI() override { std::cout << "I am derived_one\n"; }
};

class derived_two : public base {
public:
    void whoAmI() override { std::cout << "I am derived_two\n"; }
};

int main() {
    base b;
    derived_one d1;
    derived_two d2;

    b.whoAmI();
    d1.whoAmI();
    d2.whoAmI();

    return 0;
}
