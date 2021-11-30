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

// NOTE: The idea of creating a matrix using a 1D vector is coming from:
// https://stackoverflow.com/a/62158456/13041067

// Related Links:
// 1. https://stackoverflow.com/q/15810171/13041067

#include <algorithm>   // std::transform
#include <chrono>      // Timing capabilities
#include <functional>  // std::bind
#include <initializer_list>
#include <iostream>     // std::ostream, std::cout
#include <stdexcept>    // std::exept
#include <type_traits>  // std::is_arithmetic, std::enable_if
#include <vector>       // std::vector

// More explicit and hairy (since C++11)
//  'std::enable_if<std::is_arithmetic<T>::value>::type' is a dependent name, so
//  we need to tell the compiler it's a name for a type with 'typename'
template <typename T,
          typename =
              typename std::enable_if<std::is_arithmetic<T>::value>::type>
// or the shorter way (since C++14 (std::enable_if_t), since
// C++17(std::is_arithmetic_v)) template <typename T, typename =
// std::enable_if_t<std::is_arithmetic_v<T>>>
class matrix {
private:
    size_t rows_;
    size_t columns_;
    std::vector<T> data_;

public:
    //////////////////
    // Constructors //
    //////////////////

    matrix() = default;
    matrix(size_t rows, size_t columns)
        : rows_(rows),
          columns_(columns),
          data_(std::vector<T>(rows * columns)) {}  // Initialized with zero
    matrix(size_t rows, size_t columns, const T &ival)
        : rows_(rows),
          columns_(columns),
          data_(std::vector<T>(rows * columns, ival)) {}
    // Best implementation
    // source: https://stackoverflow.com/a/69822016/13041067 (My answer, with
    // the help of Bob)
    matrix(std::initializer_list<std::initializer_list<T>> imat)
        : rows_{imat.size()},
          // Minimal validation
          columns_{imat.size() ? imat.begin()->size() : 0} {
        // Check if all of the rows are of the same size
        // if (rows_.size() != imat.begin()->size())
        //     throw std::invalid_argument(
        //             "Wrong number of columns in one row!");

        // Eliminate reallocations as we already know the size of the matrix
        data_.reserve(rows_ * columns_);
        for (auto const &row : imat) {
            data_.insert(data_.end(), row.begin(), row.end());
        }
    }

    // // emplace_back() is slow when the matrix size is huge
    // matrix(std::initializer_list<std::initializer_list<T>> imat) // ✓
    //     : rows_(imat.size()),
    //       columns_(imat.begin()->size()) {
    //     for (auto &row : imat) {
    //         // Check if all of the rows are of the same size
    //         if (row.size() != imat.begin()->size())
    //             throw std::invalid_argument(
    //                 "Wrong number of columns in one row!");
    //         data.reserve(rows * columns);
    //         for (auto &col : row) {
    //             data_.emplace_back(col);
    //         }
    //     }
    // }

    // // push_back() is slow when the matrix size is huge
    // matrix(std::initializer_list<std::initializer_list<T>> imat) // ✓
    //     : rows_(imat.size()),
    //       columns_(imat.begin()->size()) {
    //     for (auto row : imat) {
    //         data_.insert(data_.end(), row.begin(), row.end());
    //     }
    // }

    // // Slightly modified version of:
    // https://stackoverflow.com/a/15810350/13041067
    // matrix(std::initializer_list<std::initializer_list<T>> imat) // ✓
    //     : matrix(imat.size(), imat.size() ? imat.begin()->size() : 0) {
    //     size_t counter = 0;
    //     for (auto &row : imat) {
    //         // Check if all of the rows are of the same size
    //         if (row.size() != imat.begin()->size())
    //             throw std::invalid_argument(
    //                 "Wrong number of columns in one row!");
    //         for (auto &col : row) {
    //             data_[counter] = col;
    //             ++counter;
    //         }
    //     }
    // }

    /// We don't need to implement other constructors becuase our class only has
    /// plain old data type and/or STL data field. These types have will be
    /// copied properly.

    //////////////
    // Functors //
    //////////////

    /// Access matrix data providing particular rows and columns
    T &operator()(size_t row, size_t column) {
        // Check if the indices are in bound
        // Idea from: https://codereview.stackexchange.com/a/155849
        if ((row - 1) >= this->num_rows() ||
            (column - 1) >= this->num_columns())
            throw std::out_of_range("Index out of bounds");

        return data_.at((row - 1) * columns_ + (column - 1));
    }

    /// For accessing elements of a constant matrix variable
    const T &operator()(size_t row, size_t column) const {
        if ((row - 1) >= this->num_rows() ||
            (column - 1) >= this->num_columns())
            throw std::out_of_range("Index out of bounds");

        return data_.at((row - 1) * columns_ + (column - 1));
    }

    // --- Member functions
    size_t num_elements() const noexcept { return rows_ * columns_; }
    // size_t num_elements() const noexcept { return data.size(); } // slower?
    size_t num_rows() const noexcept { return rows_; }
    size_t num_columns() const noexcept { return columns_; }

    //////////////////////////
    // Non-member functions //
    //////////////////////////

    // // (std::transform + std::bind)
    // // source: https://stackoverflow.com/a/3885136/13041067 (with errors)
    // // C++17 is required ?
    // friend matrix operator*(const matrix &lhs, const T &scale) {
    //     matrix out_mat(lhs.num_rows(), lhs.num_columns());
    //     std::transform(lhs.data_.begin(), lhs.data_.end(),
    //                    out_mat.data_.begin(),
    //                    std::bind(std::multiplies<T>(), std::placeholders::_1,
    //                              std::ref(scale)));
    //                             //    ^ If by any chance scale changes it
    //                             captures it. (?)
    //     return out_mat;
    // }

    // My implementation (std::transform + lambda expression)
    // My answer to stackoverflow question:
    //     https://stackoverflow.com/a/69996693/13041067
    friend matrix operator*(const matrix &lhs, const T &scale) {
        // Check if elements of both matrices are arithmetic
        // Type traits
        if (std::is_arithmetic<T>::value == false)
            static_assert(std::is_arithmetic<T>::value,
                          "ERROR: Invalid data type for a matrix. "
                          "Use an arithmetic data type!");

        matrix out_mat(lhs.num_rows(), lhs.num_columns());
        std::transform(lhs.data_.begin(), lhs.data_.end(),
                       out_mat.data_.begin(),
                       [&scale](T element) { return element *= scale; });
        return out_mat;
    }

    friend matrix operator*(const matrix &lhs, const matrix &rhs) {
        // Check if matrices are elgible for multiplication
        // if not throw an exception
        // lhs.num_columns() ?= rhs.num_rows()
        if (lhs.num_columns() != rhs.num_rows())
            throw std::invalid_argument(
                "ERROR: Matrices have invalid sizes for "
                "multiplications!\n\tThey ought to be "
                "in the form: A(a, N) * B(N, b).");

        // // Check for valid matrix elements (Using type_traits and exception)
        // if (std::is_arithmetic<T>::value == false)
        //     static_assert(std::is_arithmetic<T>::value,
        //                   "ERROR: Invalid data type for a matrix. Use an
        //                   arithmetic data type!");

        matrix result(lhs.num_rows(), rhs.num_columns());

        for (size_t row = 0; row < lhs.num_rows(); ++row)
            for (size_t col = 0; col < rhs.num_columns(); ++col)
                for (size_t inner = 0; inner < lhs.num_columns();
                     ++inner)  // or rhs.num_columns
                    result(row + 1, col + 1) +=
                        lhs(row + 1, inner + 1) * rhs(inner + 1, col + 1);

        return result;
    }

    friend bool operator==(const matrix &lhs, const matrix &rhs) {
        // Both vecotrs must be of the exact same size
        if (lhs.num_rows() != rhs.num_rows() &&
            lhs.num_columns() != rhs.num_columns())
            throw std::invalid_argument("ERROR: Difference in matrix size");

        // There is an overloaded '==' operator for vector class
        // Read more in: https://stackoverflow.com/a/16422594/13041067
        return lhs.data_ == rhs.data_;
    }
    friend bool operator!=(const matrix &lhs, const matrix &rhs) {
        return !(lhs == rhs);
    }
    friend std::ostream &operator<<(std::ostream &os, const matrix &m) {
        // Each row in the matrix
        for (size_t row = 0; row < m.rows_; ++row) {
            // Each column in the row
            for (size_t col = 0; col < m.columns_; ++col) {
                os << m.data_[row * m.columns_ + col];
                // Don't add trailing space at the end
                if (col == (m.columns_ - 1)) break;
                os << " ";  // Is there any data locality problem?
            }
            // Don't add '\n' at the end (let the user add it)
            if (row == (m.rows_ - 1)) break;
            os << '\n';
        }
        return os;
    }
};

int main() {
    // // TODO comment-in the following code as needed to test your
    // implementation
    // // above.
    // matrix<double> a(3, 3, 3);
    // std::cout << a << '\n';
    // std::cout << "a * 2:\n" a * 2 << '\n';
    // matrix<double> b(3, 3, 4);
    // auto start = std::chrono::steady_clock::now();
    // matrix<double> c = a * b;
    // auto end = std::chrono::steady_clock::now();
    // auto duration =
    //     std::chrono::duration_cast<std::chrono::nanoseconds>(end - start)
    //         .count();
    // std::cout << "multiplied a:\n";
    // std::cout << a << '\n';
    // std::cout << "with b:\n";
    // std::cout << b << '\n';
    // std::cout << "in " << duration << "ns\n";
    // std::cout << "result is:\n";
    // std::cout << c << '\n';

    // matrix<double> d = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    // std::cout << d << '\n';
    // std::cout << d(2, 3) << '\n';
    // matrix<double> e = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    // start = std::chrono::steady_clock::now();
    // matrix<double> f = d * e;
    // end = std::chrono::steady_clock::now();
    // duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end -
    // start)
    //                .count();
    // std::cout << "multiplied d:\n";
    // std::cout << d << '\n';
    // std::cout << "with e:\n";
    // std::cout << e << '\n';
    // std::cout << "in " << duration << "ns\n";
    // std::cout << "result is:\n";
    // std::cout << f << '\n';
    return 0;
}
