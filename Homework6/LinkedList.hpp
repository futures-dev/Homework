//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 24.02.2016
//

#include <stdexcept>

template<class T>
LinkedList<T>::LinkedList() {
    //sentinel creation
    pPreHead = new Node<T>;
    pPreHead->next = nullptr;
}

template<class T>
LinkedList<T>::~LinkedList() {
    // delete owned nodes
    Node<T> *current = pPreHead->next;
    while (current) {
        delete pPreHead;
        pPreHead = current;
        current = pPreHead->next;
    }
    // delete sentinel
    delete pPreHead;

}

template<class T>
Node<T> *LinkedList<T>::getPreHead(void) {
    return pPreHead;
}

template<class T>
T &LinkedList<T>::operator[](int i) {
    int j = 0;
    Node<T> *current = pPreHead;

    // sentinel not counted
    while (j <= i) {
        if (current == nullptr) {
            throw std::out_of_range("Index out of bounds");
        }
        current = current->next;
        j++;
    }
    return current->value;
}

template<class T>
int LinkedList<T>::size() {
    // size not stored
    Node<T> *current = pPreHead;
    int j = 0;
    while (current->next) {
        current = current->next;
        j++;
    }
    return j;
}

template<class T>
void LinkedList<T>::addElementToEnd(T &value) {
    // find end
    Node<T> *current = pPreHead;
    while (current->next) {
        current = current->next;
    }
    // add
    current->next = new Node<T>();
    current->next->value = value;
}

template<class T>
void LinkedList<T>::deleteNodes(Node<T> *pNodeBefore, Node<T> *pNodeLast) {
    Node<T> *last = pNodeLast->next;
    // delete until point after last
    while (pNodeBefore->next != last) {
        Node<T> temp = pNodeBefore->next;
        pNodeBefore->next = pNodeBefore->next->next;
        delete temp;
    }
}

template<class T>
void LinkedList<T>::deleteNextNode(Node<T> *pNodeBefore) {
    Node<T> *temp = pNodeBefore->next;
    pNodeBefore->next = pNodeBefore->next->next;
    delete temp;
}

template<class T>
void LinkedList<T>::addNodesToEnd(Node<T> *pNodeBefore, Node<T> *pNodeLast) {
    // find end
    Node<T> *current = pPreHead;
    while (current->next) {
        current = current->next;
    }
    // add
    current->next = pNodeBefore->next;
    pNodeBefore->next = pNodeLast->next;
    pNodeLast->next = nullptr; // end.next should be nullptr
}

template<class T>
void LinkedList<T>::addNodeToEnd(Node<T> *pNodeBefore) {
    Node<T> *current = pPreHead;
    while (current->next) {
        current = current->next;
    }
    current->next = pNodeBefore->next;
}

template<class T>
void LinkedList<T>::moveNodesAfter(Node<T> *pNode, Node<T> *pNodeBefore, Node<T> *pNodeLast) {
    // self-describing
    Node<T> *after = pNode->next;
    pNode->next = pNodeBefore->next;
    pNodeBefore->next = pNodeLast->next;
    pNodeLast->next = after;
}

template<class T>
void LinkedList<T>::moveNodeAfter(Node<T> *pNode, Node<T> *pNodeBefore) {
    Node<T> *after = pNode->next;
    pNode->next = pNodeBefore->next;
    pNodeBefore->next = pNodeBefore->next->next;
    pNode->next->next = after;
}


