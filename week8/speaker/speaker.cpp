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

// Interface
struct greetings {
    virtual ~greetings() = default;
    virtual void say_hello() = 0;
    virtual void say_goodbye() = 0;
};

// Interface
struct politeness {
    virtual ~politeness() = default;
    virtual void say_please() = 0;
    virtual void say_thanks() = 0;
    virtual void say_youre_welcome() = 0;
};

// No need to specify the inheritance access specifier as we inherit from
// structs, they are by default public
class speaker : greetings, politeness {
public:
    void say_hello() override { std::cout << "Hello" << '\n'; }
    void say_goodbye() override { std::cout << "Goodbye" << '\n'; }
    void say_please() override { std::cout << "Please" << '\n'; }
    void say_thanks() override { std::cout << "Thanks" << '\n'; }
    void say_youre_welcome() override { std::cout << "You're Welcome" << '\n'; }
};

int main() {
    speaker spkr;
    spkr.say_hello();
    spkr.say_goodbye();
    spkr.say_please();
    spkr.say_thanks();
    spkr.say_youre_welcome();
    return 0;
}
