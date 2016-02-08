//
// Andrei Kolomiets 143-1
// CLion 1.2.1 MinGW 3.4.1
// 08.02.2016
//
#include "safearray.h"

#ifndef HOMEWORK_ENHANCEDSAFEARRAY_H
#define HOMEWORK_ENHANCEDSAFEARRAY_H

/*
 * SafeArray supporting extra features:
 *  copy constructor;
 *  size getter;
 *  assignment operator overload;
 *  equality operator overload.
 */
template<class T>
class EnhancedSafeArray : public SafeArray<T> {
public:

    /*
     * Default constructor: zero-capacity EnhancedSafeArray
     */
    EnhancedSafeArray<T>(void) : SafeArray<T>() { }

    /*
     * Constructor based on a given capacity
     */
    EnhancedSafeArray<T>(size_t n) : SafeArray<T>(n) { }

    /*
     * Copy constructor. Deep copy of storage.
     */
    EnhancedSafeArray<T>(const EnhancedSafeArray &other) : SafeArray<T>(other.count) {
        std::copy(other.storage, &other.storage[other.count], this->storage);
    }

    /*
     * Returns storage capacity
     */
    size_t size() const {
        return this->count;
    }

    /*
     * Assignment operator overload. Delete and deep copy of storage.
     */
    T &operator=(EnhancedSafeArray const &other) {
        // storage may be NULL
        if (this->storage) {
            delete[] this->storage;
        }
        this->count = other.count;
        this->storage = new T[this->count];
        std::copy(other.storage, &other.storage[other.count], this->storage);
    }

    /*
     * Equality operator overload. Returns true if sizes and each element are equal.
     */
    bool operator==(EnhancedSafeArray const &other) {
        if (this->count == other.count) {
            for (int i = 0; i < this->count; i++) {
                if ((*this)[i] != other[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

};


#endif //HOMEWORK_ENHANCEDSAFEARRAY_H
