/**
 * @file hash.h
 * @brief Use this to create hash table data structure
 *
 * @note Enjoy hashing
 * @author Ali Bozorgzadeh
 * @version 1.0
 * @bug No bugs known!
 * @date 12/14/21  1:38am
 *
 * Contact: aliiiib95@gmail.com
 *
 * Created on: 12/14/21  1:42am
 *
 */

#ifndef HASH
#define HASH

#include <iostream>
#include <string>   // std::string
#include <utility>  // std::pair, std::make_pair
#include <vector>   // std::vector

/**
 * This class is a simple implementation of the [**hash
 * table**](https://en.wikipedia.org/wiki/Hash_table) data structure.
 * A Hash table, \f$H\f$, is a data structure that stores the values \f$v_i\f$
 * that are associated with keys \f$k_i\f$.
 *
 * Assumptions:
 *   - We assume that keys are unique.
 *      - But note that their [hash
 *      code](https://en.wikipedia.org/wiki/Hash_function) may not be unique
 *   - Only associate `std::string` with variables of an arbitrary type
 *   - Using <a href="https://en.wikipedia.org/wiki/Linear_probing">linear
 *   probing</a> for [hash
 *   collision](https://en.wikipedia.org/wiki/Hash_collision) cases
 * */
template <typename T>
class HTable {
private:
    /// @brief Here we restrict ourselves to only associate `std::string`s
    /// with variables of an arbitrary type.
    std::vector<std::pair<std::string, T>> data;
    /// @brief To keep track of used positions in the hash table
    std::vector<bool> positions_in_use;

public:
    /**
     * @brief Constructor which creates a hash table of certain size
     * @param size size of the hash table
     * @return a hash table
     *
     * You don't want to create an empty hash table as the 'insert' member
     * function does not push_back
     */
    HTable(size_t size) : data(size), positions_in_use(size) {}

    /**
     * @brief Compute the hash of a given string (hash function)
     * @param key the key for which it computes hash code
     * @return a hash code (might be unique, or not)
     *
     * If the size of your hash table is small your going to have a lot of hash
     * code collisions.
     *
     * \par
     * since `hash_val` is an `unsigned` type we can just ignore overflows
     * (overflow is well-defined for unsigned types)
     *
     * \par
     * Because we need a value between `0` and `size - 1`, we take the
     * remainder of division by table's size
     */
    size_t hash(const std::string &key) {
        size_t hash_val = 5381;  // have a nice prime number
        for (const char c : key) {
            hash_val = hash_val * 33 + c;
        }
        return hash_val % data.size();
    }

    /**
     * @brief Inserts a key-value pair into the hash table (if possible)
     * @param key the key of the pair
     * @param value the value of the pair
     * @return false if there was no hash collisions
     * @return true if it had to do linear probing
     *
     * \exception std::runtime_error If it can't find an empty room it will
     * throw an exception
     *
     * If there is a hash collisions it will do an open address hashing, in
     * this case linear probing.
     */
    bool insert(const std::string &key, const T &value) {
        size_t pos = hash(key);

        if (positions_in_use[pos] == false) {
            positions_in_use[pos] = true;
            data[pos] = std::make_pair(key, value);

            return false;
        }

        // No checks for duplicate entries

        // At this point we have collision
        size_t table_size = data.size();
        // TODO: Neither efficient nor readable
        for (size_t p = pos + 1; (p < table_size) && (p != pos);
             p = (p + 1) % table_size) {
            if (positions_in_use[p] == false) {
                positions_in_use[p] = true;
                data[p] = std::make_pair(key, value);
                return true;
            }
        }

        // At this point there is no empty position
        throw std::runtime_error("ERROR: Could not insert " + key +
                                 ". The hash table is full.");
    }

    /**
     * @brief gets the value associated with the given key (with collision in
     * mind)
     * @param key the key of the key-value pair
     * @return the value associated with the given key in the key-value pair
     *
     * \exception std::runtime_error If it can't find the pair it will throw an
     * exception
     */
    T &get(const std::string &key) {
        size_t pos = hash(key);

        // If the user-provided key is the same as the key stored in table, It
        // means there is no collision
        if (key == data[pos].first) {
            return data[pos].second;
        }

        // At this point we have collision -> linear probing
        size_t table_size = data.size();
        for (size_t p = pos + 1; (p < table_size) && (p != pos);
             p = (p + 1) % table_size) {
            if (key == data[p].first) {
                return data[p].second;
            }
        }

        // At this point there is no empty position
        throw std::runtime_error("ERROR: The entry " + key +
                                 " could not be found in the table.");
    }

    /**
     * @brief Overload of the <code>operator\<\<</code>
     * @param os output stream
     * @param h the hash table to be fed to the output stream <code>os</code>
     * @return output stream that will be shoved into the std::cout at some
     * point by the user
     *
     * It will omit the new line for the last pair (delegates the responsiblity
     * to the user)
     */
    friend std::ostream &operator<<(std::ostream &os, const HTable &h) {
        size_t table_size = h.data.size();
        for (size_t p = 0; p < table_size; ++p) {
            os << "(" << h.data[p].first << ", " << h.data[p].second << ")";
            // Do not add newline at the end
            if (p == table_size - 1) break;
            os << '\n';
        }

        return os;
    }

    /**
     * @brief removes a key-value pair form the hash table and reset its
     * position so that it can be used later use
     * @param key the key of the pair we wish to erase
     *
     * \exception std::runtime_error If it can't find the pair it will throw an
     * exception
     *
     * Again it will do a linear probing for the collision cases.
     */
    void erase(const std::string &key) {
        size_t pos = hash(key);
        const auto pos_it = data.begin() + pos;
        const auto value = get(key);

        // If no collision
        if (data[pos].second == value) {  // No need to compare keys
            // Erase the data element at position pos (iterator)
            data.erase(pos_it);
            // Add an new empty data element into the previously removed element
            data.insert(pos_it, std::pair<std::string, T>());
            // Now that element is empty
            positions_in_use[pos] = false;
            return;
        }

        // At this point we have collision -> linear probing
        size_t table_size = data.size();
        const auto data_begin_it = data.begin();
        auto it = data_begin_it;
        for (size_t p = pos + 1; (p < table_size) && (p != pos);
             p = (p + 1) % table_size) {
            it = data_begin_it + p;
            if (it->first == key) {
                data.erase(it);
                // Note that at this point, `it` is an invalidated pointer,
                // and you cannot dereference it.
                data.insert(data.begin() + p, std::pair<std::string, T>());
                positions_in_use[it - data.begin()] = false;
                return;
            }
        }

        // At this point they provided key is not found in the hash table
        throw std::runtime_error("ERROR: Could not erase " + key +
                                 " , as it is not in the table.");
    }

    /**
     * @brief clears the whole table (basically resets it)
     * @warning If the table is empty it will write a message to stderr to
     * inform the user that they are clearing an empty table
     */
    void clear() {
        // If hash table is of size zero don't do anything
        if (!data.size()) {
            std::cerr << "The hash table is of size zero!\n";
            return;
        }

        // Erase all even numbers (C++11 and later)
        const auto data_begin_it = data.begin();
        for (auto it = data_begin_it; it != data.end(); ++it) {
            it->first = "";
            it->second = T();
            positions_in_use[it - data_begin_it] = false;
        }
    }
};

#endif  // !HASH
