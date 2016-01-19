//
// Created by Andrei on 18.01.2016.
//

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
};

PointArray::PointArray(const Point *points, const int size) {
    _storage = new Point[_size = size];
    for (int i = 0; i < size; i++) {
        _storage[i] = points[i];
    }
}

PointArray::PointArray(const PointArray &pv) : PointArray(pv._storage, pv._size) {
}

PointArray::~PointArray() {
    delete[] _storage;
}

void PointArray::push_back(const Point &p) {
    resize(_size + 1);
    _storage[_size++] = p;
}

void PointArray::insert(const int position, const Point &p) {
    resize(_size + 1);
    for (int i = _size; i > position; i--) {
        _storage[i] = _storage[i - 1];
    }
    _storage[position] = p;
    _size++;
}

void PointArray::remove(const int position) {
    for (int i = position; i < _size; i++) {
        _storage[i] = _storage[i + 1];
    }
    resize(--_size);
}

const int PointArray::getSize() const {
    return _size;
}

void PointArray::clear() {
    resize(_size = 0);
}

Point *PointArray::get(const int position) {
    return (&_storage)[position];
}

const Point *PointArray::get(const int position) const {
    return (&_storage)[position];
}

void PointArray::resize(int n) {
    Point *new_storage = new Point[n];
    if (n > _size) {
        n = _size;
    }
    _size = n;
    // todo: use memcpy
    for (int i = 0; i < n; i++) {
        new_storage[i] = _storage[i];
    }
    delete[] _storage;
    _storage = new_storage;
}
