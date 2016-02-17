//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 15.02.2016 
#ifndef HOMEWORK_NICEQUEUE_HPP
#define HOMEWORK_NICEQUEUE_HPP


template<class T>
NiceQueue<T>::NiceQueue(size_t capacity) : m_capacity(capacity), inStack(capacity), outStack(capacity) { }

template<class T>
size_t NiceQueue<T>::size(void) const {
    return inStack.size() + outStack.size();
}

template<class T>
void NiceQueue<T>::enq(T newelement) throw(out_of_range) {
    // out of range exception will be thrown in stack if relevant
    inStack.push(newelement);
}

template<class T>
T NiceQueue<T>::deq(void) throw(out_of_range) {
    if (outStack.size() > 0) {
        return outStack.pop();
    }
    else {
        int n = inStack.size();
        for (int i = 0; i < n; i++) {
            outStack.push(inStack.pop());
        }
        // out of range exception will be thrown in stack if relevant
        return outStack.pop();
    }
}

template<class T>
T NiceQueue<T>::getMinimum(void) throw(out_of_range) {
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