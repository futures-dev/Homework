#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#include <stdexcept> // out_of_range

template<class T>
class safearray {

private:
    T *_storage;
    int _capacity;

public:
    safearray() : _storage(nullptr), _capacity(0) { } // default constructor
    safearray(int cap) : _storage(new T[cap]), _capacity(cap) { } // single param constructor

    // destructor
    ~safearray(void) {
        if (_storage) {
            delete[] _storage;
        }
    }

    // indexer
    T &operator[](int index) {
        if (index < 0 || index > _capacity) {
            throw std::out_of_range(std::string("Index ").append(std::to_string(index)).append(" is out of bounds."));
        }
        else {
            return _storage[index];
        }
    }
};

#endif
