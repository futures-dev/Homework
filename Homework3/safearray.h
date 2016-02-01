#ifndef SAFEARRAY_H
#define SAFEARRAY_H

template<class T>
class safearray {

private:
    T *_storage;
    int _capacity;

public:
    safearray() : _storage(nullptr), _capacity(0) { } // default constructor
    safearray(int); // single param constructor
    ~safearray(void); // destructor
    T &operator[](int);
};

#endif
