//
// Created by Andrei on 18.01.2016.
//

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

PointArray::PointArray() {

}

PointArray::PointArray(const ::PointArray::Point *points, const int size) {

}

PointArray::PointArray(const ::PointArray::PointArray &pv) {

}

PointArray::~PointArray() {

}

void PointArray::push_back(const ::PointArray::Point &p) {

}

void PointArray::insert(const int position, const ::PointArray::Point &p) {

}

void PointArray::remove(const int position) {

}

const int PointArray::getSize() const {
    return 0;
}

void PointArray::clear() {

}

Point *PointArray::get(const int position) {
    return nullptr;
}

const Point *PointArray::get(const int position) const {
    return nullptr;
}

void PointArray::resize(int n) {

}
