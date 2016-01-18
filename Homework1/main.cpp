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

int main(int argc, char **argv) {
    // Point tests
    testPointDefaultConstructor();
    testPointConstructor();
    testPointModifiers();

    // ...
    // You can create and call additional checks here

    return EXIT_SUCCESS;
}

