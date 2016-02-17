//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 15.02.2016 
#ifndef HOMEWORK_NICEQUEUE_HPP
#define HOMEWORK_NICEQUEUE_HPP


template<class T>
NiceQueue<T>::NiceQueue(size_t capacity) : inStack(capacity), outStack(capacity) {

}

template<class T>
size_t NiceQueue<T>::size(void) const {
    return 0;
}

template<class T>
void NiceQueue<T>::enq(T newelement) throw(out_of_range) {

}

template<class T>
T NiceQueue<T>::deq(void) throw(out_of_range) {
    return 0;
}

template<class T>
T NiceQueue<T>::getMinimum(void) throw(out_of_range) {
    return 0;
}

#endif //HOMEWORK_NICEQUEUE_HPP