/* 
 * File:   geometry.h
 * Declaration of class Point and PointArray
 * You should write your function definitions in a file called geometry.cpp.
 * Do not modify this file.
 */

#ifndef EX1_POINT_GEOMETRY_H
#define    EX1_POINT_GEOMETRY_H

class Point {
public :
    Point(int x = 0, int y = 0);

    int getX() const;

    int getY() const;

    void setX(const int new_x);

    void setY(const int new_y);

private :
    int _x, _y;

};

class PointArray {
public:
    // Default constructor (a constructor with no arguments)
    // It should create an array with size 0.
    PointArray();

    // Point array called points and an int called size
    // as its arguments. It should initialize a PointArray with the
    // specified size, copying the values from points. You will need
    // to dynamically allocate the PointArray’s internal array to the
    // specified size.
    PointArray(const Point points[], const int size);

    // Constructor that creates a copy of a given PointArray (a copy
    PointArray(const PointArray &pv);

    // Destructor that deletes the internal array of the PointArray
    ~PointArray();

    // Add a Point to the end of the array
    void push_back(const Point &p);

    // Insert a Point at some arbitrary position (subscript) of the array,
    // shifting the elements past position to the right
    void insert(const int position, const Point &p);

    // Remove the Point at some arbitrary position (subscript) of the array,
    // shifting the remaining elements to the left
    void remove(const int position);

    // Get the size of the array
    const int getSize() const;

    // Remove everything from the array and sets its size to 0
    void clear();

    // Get a pointer to the element at some arbitrary position in the array,
    // where positions start at 0 as with arrays
    Point *get(const int position);

    const Point *get(const int position) const;

protected:
    // Allocates a new array of size n, copies the first min (previous array
    // size, n) existing elements into it, and deallocates the old array.
    void resize(int n);

private :
    Point *_storage;
    int _size;
};

#endif	/* EX1_POINT_GEOMETRY_H */

