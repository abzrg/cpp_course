## Question
Why is it a good idea to explicitly specify functions that override a virtual
function with the keyword `override`?  Describe a scenario where one gets into
huge trouble when not having specified overriding functions as override!

Two scenario could be considered, if you omit the `override` keyword:

1. Your colleges, sees the code and thinks it's a member function and may alter
   its signature so that it is no longer inherited from base
2. If the name of the function in the base class changes, then we have a new
   member function in the derived class.
3. Compiler can no more check the base class to see if there even exists a
   virtual function to override. Also it no longer emit warnings/errors for
   adding/altering new methods that you think they are overrides.
   ([source](https://stackoverflow.com/a/18198377/13041067))


## A small note (from [stackoverflow](https://stackoverflow.com/a/18198501/13041067))
`override` **is not a keyword**, but a _special_ kind of identifier! It has
meaning only in the context of declaring/defining virtual functions, in other
contexts it's just an ordinary **identifier**. For details read 2.11.2 of _The
Standard_. (It's essentially because of backward compatibility; you can't just
suddenly add new keyword into the language)

```cpp
#include <iostream>

struct base
{
    virtual void foo() = 0;
};

struct derived : base
{
    virtual void foo() override
    {
        std::cout << __PRETTY_FUNCTION__ << std::endl; // print the function (foo) signature
    }
};

int main()
{
    base* override = new derived();
    override->foo();
    return 0;
}
```

Output:

```sh
    $ g++ -std=c++11 -o override-test override-test.cc
    $ ./override-test
    virtual void derived::foo()
```
