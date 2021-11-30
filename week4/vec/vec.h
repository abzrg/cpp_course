#ifndef VEC_H_
#define VEC_H_

#include <initializer_list>
#include <iostream>
#include <utility>

class vec {
private:
    // Variable to store the number of elements contained in this vec.
    size_t elements;
    // Pointer to store the address of the dynamically allocated memory.
    double *data;

public:
    // --- Constructors

    /// Creates a vec variable of size 'size'.
    /// This constructor has to allocate an array of 'size' double variables.
    vec(size_t size);

    /// Creates a vec variable of size 'size' and to initialize all entires with
    /// the value of 'ival'. This constructor has to allocate an array of 'size'
    /// double variables and initialize all of its elements with the value of
    /// 'ival'.
    vec(size_t size, double ival);

    /// Creates a vec variable with the contents of 'ilist'.
    vec(std::initializer_list<double> ilist);

    // --- Destructor

    /// Deallocates the dynamically allocated heap memory.
    ~vec();

    // --- Copy/Move constructor/assignment operator

    /// Copy constructor that creates a copy of the vec variable 'v'.
    vec(const vec &v);

    /// Copy assignment operator. Creates a copy of vec variable 'v'.
    vec &operator=(const vec &v);

    /// Move constructor that steals the data of the vec variable 'v'.
    vec(vec &&v);

    /// Move assignment operator. Moves from the vector variable 'v'.
    vec &operator=(vec &&v);

    // --- Other methods

    /// Returns the number of elements of the vector.
    size_t size() const;

    // --- Operators

    /// Returns a reference to the value at position 'idx'.
    /// This function does not perform a range check.
    double &operator[](size_t idx);

    /// Returns a reference to the value at position 'idx'.
    /// This function does not perform a range check.
    /// See the lecture sildes for the reason why we have to provide a const
    /// version of this operator as well.
    const double &operator[](size_t idx) const;

    /// Writes the elements stored in the vec 'v' to the output stream 'os'.
    /// A variable of type vec can then be printed using std::cout << ...
    friend std::ostream &operator<<(std::ostream &os, const vec &v);

    /// Performs an entry-wise addition. Since we pass 'lhs' by value (so we
    /// create a copy of it), you can add 'rhs's entires to 'lhs' return it.
    friend vec operator+(vec lhs, const vec &rhs);

    /// Performs an entry-wise substraction. Since we pass 'lhs' by value (so we
    /// create a copy of it), you can subtract 'rhs's entires to 'lhs' and
    /// return it.
    friend vec operator-(vec lhs, const vec &rhs);

    /// Multiplies each entry with the value of 'scale'.
    /// Since we pass 'lhs' by value (so we create a copy of it), you can
    /// multiply each of it's entries by 'scale' and return it.
    friend vec operator*(vec lhs, double scale);

    /// Computes the scalar product of two vectors.
    friend double operator*(const vec &lhs, const vec &rhs);
};

#endif  // VEC_H_
