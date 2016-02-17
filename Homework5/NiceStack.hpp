//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 15.02.2016 
//

#ifndef HOMEWORK_NICESTACK_HPP
#define HOMEWORK_NICESTACK_HPP

template<class T>
NiceStack<T>::NiceStack(size_t capacity) : iHead(0), m_capacity(capacity), storage(capacity) { }

template<class T>
size_t NiceStack<T>::size() const {
    return iHead;
}

template<class T>
NiceStack<T>::~NiceStack(void) {
}

template<class T>
void NiceStack<T>::push(T newelement) throw(out_of_range) {
    if (size() == m_capacity) {
        throw out_of_range("Attempt to push into a full stack.");
    }
    if (size() == 0) {
        storage.push_back(TypeElementStack(newelement, newelement));
    }
    else {
        storage.push_back(
                TypeElementStack(newelement, newelement < storage.back().second ? newelement : storage.back().second));
    }
    iHead++;
}

template<class T>
T NiceStack<T>::pop(void) throw(out_of_range) {
    if (size() == 0) {
        throw out_of_range("Attempt to pop from an empty stack.");
    }
    T v = storage.back().first;
    storage.pop_back();
    iHead--;
    return v;
}

template<class T>
T NiceStack<T>::getMinimum(void) throw(out_of_range) {
    if (size() == 0) {
        throw out_of_range("Attempt to get minimum of an empty stck.");
    }
    return storage.back().second;
}


#endif //HOMEWORK_NICESTACK_HPP
