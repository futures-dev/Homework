//
// Andrei Kolomiets 143-1
// CLion 1.2 cpp 5.2.1
// 17.02.2016
//

#ifndef HOMEWORK_NICEQUEUE_HPP
#define HOMEWORK_NICEQUEUE_HPP

/*
 * Constructs a NiceQueue obejct with given capacity
 */
template<class T>
NiceQueue<T>::NiceQueue(size_t capacity) : m_capacity(capacity), inStack(capacity), outStack(capacity) { }

/*
 * Returns number of elements in the queue
 */
template<class T>
size_t NiceQueue<T>::size(void) const {
    return inStack.size() + outStack.size();
}

/*
 * Inserts an element into the queue
 */
template<class T>
void NiceQueue<T>::enq(T newelement) throw(out_of_range) {
    // out of range exception will be thrown in stack if relevant
    inStack.push(newelement);
}

/*
 * Returns first element of the queue and removes it
 */
template<class T>
T NiceQueue<T>::deq(void) throw(out_of_range) {
    // first, try to pop outStack
    if (outStack.size() > 0) {
        return outStack.pop();
    }
    else {
        // then, move elements from inStack to outStack
        int n = inStack.size();
        for (int i = 0; i < n; i++) {
            outStack.push(inStack.pop());
        }
        // finally, pop outStack
        // out of range exception will be thrown in stack if relevant
        return outStack.pop();
    }
}

/*
 * Returns minimum of the queue elements
 */
template<class T>
T NiceQueue<T>::getMinimum(void) throw(out_of_range) {
    // minimum of inStack and outStack minima
    if (outStack.size() == 0) {
        if (inStack.size() == 0) {
            throw out_of_range("Attempt to get minimum of an empty queue");
        }
        return inStack.getMinimum();
    }
    if (inStack.size() == 0) {
        return outStack.getMinimum();
    }
    return min(inStack.getMinimum(), outStack.getMinimum());
}

#endif //HOMEWORK_NICEQUEUE_HPP