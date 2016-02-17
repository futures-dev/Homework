//
// Andrei Kolomiets 143-1
// CLion 1.2 cpp 5.2.1
// 17.02.2016
//

#ifndef HOMEWORK_NICESTACK_HPP
#define HOMEWORK_NICESTACK_HPP

/*
 * Constructs a NiceStack with given capacity
 */
template<class T>
NiceStack<T>::NiceStack(size_t capacity) : iHead(0), m_capacity(capacity), storage(capacity) { }

/*
 * Returns current stack size
 */
template<class T>
size_t NiceStack<T>::size() const {
    return iHead;
}

/*
 * Destructor not required because storage vector is a non-pointer member
 */
template<class T>
NiceStack<T>::~NiceStack(void) { }

/*
 * Inserts an element in the stack
 */
template<class T>
void NiceStack<T>::push(T newelement) throw(out_of_range) {
    if (size() == m_capacity) {
        throw out_of_range("Attempt to push into a full stack.");
    }
    if (size() == 0) {
        // current minimum is the only element
        storage.push_back(TypeElementStack(newelement, newelement));
    }
    else {
        // current minimum is min(current minimum, new elem)
        storage.push_back(
                TypeElementStack(newelement, newelement < storage.back().second ? newelement : storage.back().second));
    }
    iHead++;
}

/*
 * Returns an element in the end of the stack and removes it
 */
template<class T>
T NiceStack<T>::pop(void) throw(out_of_range) {
    if (size() == 0) {
        throw out_of_range("Attempt to pop from an empty stack.");
    }
    // value stored in first
    T v = storage.back().first;
    // remove
    storage.pop_back();
    iHead--;
    return v;
}

/*
 * Return minimum of the stack elements
 */
template<class T>
T NiceStack<T>::getMinimum(void) throw(out_of_range) {
    if (size() == 0) {
        throw out_of_range("Attempt to get minimum of an empty stck.");
    }
    // no remove
    return storage.back().second;
}


#endif //HOMEWORK_NICESTACK_HPP
