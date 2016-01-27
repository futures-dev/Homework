//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 19.01.2016
//

// #include <string.h> ; for memcpy
#include <stdexcept>
// for range_error
#include "geometry.h"

Point::Point(int x, int y) {
    setX(x);
    setY(y);
}

int Point::getX() const {
    return _x;
}

int Point::getY() const {
    return _y;
}

void Point::setX(const int new_x) {
    _x = new_x;
}

void Point::setY(const int new_y) {
    _y = new_y;
}

PointArray::PointArray() :
        PointArray(nullptr, 0) {
    // Default constructor initializes 0-size array and sets size 0
};

PointArray::PointArray(const Point *points, const int size) {
    if (size < 0) {
        throw std::range_error("Array size is negative");
    }
    _storage = new Point[_size = size]; // array init
    for (int i = 0; i < size; i++) {
        _storage[i] = points[i]; // values insertion
    }
}

PointArray::PointArray(const PointArray &pv) : PointArray(pv._storage, pv._size) {
    // Copy constructor directs array of points and size to PointArray(const Point*, const int)
}

PointArray::~PointArray() {
    delete[] _storage;
}

void PointArray::push_back(const Point &p) {
    resize(_size + 1); // creating space in the back
    _storage[_size - 1] = p; // value insertion
}

void PointArray::insert(const int position, const Point &p) {
    if (position > _size || position < 0) {
        throw std::range_error("Insert position out of range");
    }
    resize(_size + 1); // creeating space for new element
    for (int i = _size - 1; i > position; i--) {
        _storage[i] = _storage[i - 1]; // shift
    }
    _storage[position] = p; // value insertion
}

void PointArray::remove(const int position) {
    if (position >= _size || position < 0) {
        throw std::range_error("Remove position out of range");
    }
    for (int i = position; i < _size - 1; i++) {
        _storage[i] = _storage[i + 1]; // shift, removed value is cleared
    }
    resize(_size - 1); // resize
}

const int PointArray::getSize() const {
    return _size;
}

void PointArray::clear() {
    resize(0); // set size 0 and resize
}

Point *PointArray::get(const int position) {
    if (position >= _size || position < 0) {
        throw std::range_error("Get position out of range");
    }
    return &(_storage[position]);
}

const Point *PointArray::get(const int position) const {
    if (position >= _size || position < 0) {
        throw std::range_error("Get position out of range");
    }
    return &(_storage)[position];
}

void PointArray::resize(int n) {
    if (n < 0) {
        throw std::range_error("New size is negative");
    }
    // resize sets _size to n
    Point *new_storage = new Point[n];
    // shall copy exactly size vaues
    if (n < _size) {
        _size = n;
    }
    for (int i = 0; i < _size; i++) {
        new_storage[i] = _storage[i]; // values copy
    }
    // could use memcpy
    // memcpy(_storage,new_storage,n*sizeof(Point));
    _size = n; // size update for n>size
    delete[] _storage; // garbage cleaning
    _storage = new_storage; // storage update
}
