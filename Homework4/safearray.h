#ifndef SAFEARRAY_H
#define SAFEARRAY_H

#include <stdexcept>

template<class T>
class SafeArray {

protected:
    T *storage;
    size_t count;

public:
    SafeArray() : storage(NULL), count(0) { } // default constructor
    SafeArray(int); // single param constructor
    ~SafeArray(void); // destructor
    T &operator[](int k);

    const T &operator[](int k) const;
};

template<class T>
SafeArray<T>::SafeArray(int n) {
    storage = new T[n];
    count = n;
}

template<class T>
SafeArray<T>::~SafeArray(void) {
    delete[] storage;
}

template<class T>
T &SafeArray<T>::operator[](int k) {
    // Another good idea create function checkBound with this check
    if (k < 0) throw std::out_of_range("Index is below 0");
    if (k >= count) throw std::out_of_range("Index is too high");
    return storage[k];
}

template<class T>
const T &SafeArray<T>::operator[](int k) const {
    // To avoid infinite recursion we need get non-const pointer to self
    SafeArray<T> &nonConstThis = const_cast <SafeArray<T> &>(*this);
    return nonConstThis[k];
}

#endif
