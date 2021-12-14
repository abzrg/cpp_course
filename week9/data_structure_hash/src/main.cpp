//===----------------------------------------------------------------------===//
//
// Ali Bozorgzadeh
//
//   <aliiiib95@gmail.com>
//
// Description
//   A simple implementation of a hash function using the linear probing
//   mechanism for collision cases
//
//
//===----------------------------------------------------------------------===//

#include "utils/hash.h"

int main() {
    // Create
    HTable<int> shopping_list(7);  // OK
    std::cout << shopping_list << '\n';

    // Insert
    shopping_list.insert("egg", 1);  // OK
    shopping_list.insert("bread", 2);
    shopping_list.insert("milk", 3);
    shopping_list.insert("flour", 4);
    shopping_list.insert("sugar", 5);
    shopping_list.insert("chocolate", 6);
    shopping_list.insert("cream", 7);
    std::cout << shopping_list << '\n';  // OK

    // No more room
    try {
        shopping_list.insert("banana", 8);  // Exception is thrown
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }

    // Read entries
    auto milk = shopping_list.get("milk");
    std::cout << "milk: " << milk << '\n';  // OK

    // Cannot find it in the table
    try {
        shopping_list.get("banana");  // Exception is thrown
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }

    // Erase entries
    shopping_list.erase("milk");
    std::cout << shopping_list << '\n';

    // Cannot find it in the table
    try {
        shopping_list.erase("milk");  // Exception is thrown
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << '\n';
    }

    // Clear a hash table
    shopping_list.clear();
    std::cout << shopping_list << '\n';

    // Clear an empty hash table
    HTable<int> empty(0);
    empty.clear();

    return 0;
}
