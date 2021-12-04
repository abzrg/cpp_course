# Week8 / Mean Template ERROR

## Encapsulation of a templated class

I modularized the code into header/implementation files. But as you might know, in C++ you
[cannot define template functions outside the header file](Why can templates only be implemented in the header file?),
otherwise you'll get an 'undefined reference to function' error. For that
matter I had to use some "preprocessing trickery!" to do the task. For details
read [this](https://stackoverflow.com/a/26816994/13041067)


## Solution to exercise and why

To know why is that, read [this](https://stackoverflow.com/a/4643295/13041067).

Another really good resource for this problem is this
[video](https://www.youtube.com/watch?v=LMP_sxOaz6g) on templates from cppcon.
