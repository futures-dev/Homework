#include <assert.h>
#include <stdlib.h>
#include <iostream> // cout
#include "geometry.h"

using namespace std;

// ============== test for Point ======================

Point testPointDefaultConstructor() {
    // Test of default constructor
    Point point;
    assert(point.getX() == 0);
    assert(point.getY() == 0);
    return point;
}

Point testPointConstructor() {
    // Test of constructor
    Point point = Point(5, 7);
    assert(point.getX() == 5);
    assert(point.getY() == 7);
    return point;
}

void testPointModifiers() {
    // Test of Modifiers
    Point point = testPointConstructor();
    point.setX(-99);
    assert(point.getX() == -99);
    assert(point.getY() == 7);
}

PointArray testPointArrayDefaultConstructor() {
    // Test of default ctor
    PointArray pointArray;
    assert(pointArray.getSize() == 0);
    return pointArray;
}

PointArray testPointArrayConstructor() {
    Point *points = new Point[2];
    points[0] = testPointConstructor();
    points[1] = testPointDefaultConstructor();
    PointArray pointArray(points, 2);
    assert(pointArray.getSize() == 2);
    assert(pointArray.get(0)->getY() == 7);
    assert(pointArray.get(1)->getX() == 0);
    return pointArray;
}

void testPointArrayPushBack() {
    PointArray pointArray = testPointArrayDefaultConstructor();
    pointArray.push_back(testPointDefaultConstructor());
    pointArray.push_back(testPointConstructor());
    assert(pointArray.getSize() == 2);
    assert(pointArray.get(0)->getY() == 0);
    assert(pointArray.get(1)->getX() == 5);
    pointArray = testPointArrayConstructor();
    pointArray.push_back(testPointDefaultConstructor());
    pointArray.push_back(testPointConstructor());
    assert(pointArray.get(pointArray.getSize() - 2)->getY() == 0);
    assert(pointArray.get(pointArray.getSize() - 1)->getX() == 5);
}

PointArray testPointArrayInsert() {
    PointArray pointArray = testPointArrayConstructor();
    pointArray.insert(1, Point(2, 3));
    assert(pointArray.getSize() == 3);
    assert(pointArray.get(1)->getX() == 2);
    assert(pointArray.get(1)->getY() == 3);
    return pointArray;
}

void testPointArrayRemoveClear() {
    PointArray pointArray = testPointArrayConstructor();
    pointArray.remove(1);

    assert(pointArray.getSize() == 2);
    assert(pointArray.get(1)->getX() == 0);
    assert(pointArray.get(1)->getY() == 0);

    pointArray.clear();
    assert(pointArray.getSize() == 0);
}

void testPointArrayInsertEmpty() {
    PointArray pointArray = testPointArrayDefaultConstructor();
    pointArray.insert(0, Point(2, 3));

    assert(pointArray.getSize() == 1);
    assert(pointArray.get(0)->getX() == 2);
    assert(pointArray.get(0)->getY() == 3);

}

int main(int argc, char **argv) {
    // Point tests
    testPointDefaultConstructor();
    testPointConstructor();
    testPointModifiers();

    // ...
    // You can create and call additional checks here
    testPointArrayDefaultConstructor();
    testPointArrayConstructor();
    testPointArrayPushBack();
    testPointArrayInsert();
    testPointArrayRemoveClear();
    testPointArrayInsertEmpty();



    return EXIT_SUCCESS;
}

