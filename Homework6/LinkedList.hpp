#include <stdexcept>

template<class T>
LinkedList<T>::LinkedList() {
    //Creation of the dummy/sentinel element
    pPreHead = new Node<T>;
    pPreHead->next = nullptr;

    // Write your code here
    // ...
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node<T> *current = pPreHead->next;
    while (current) {
        delete pPreHead;
        pPreHead = current;
        current = pPreHead->next;
    }
    // Delete sentinel
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
    Node<T> *current = pPreHead;
    while (current->next) {
        current = current->next;
    }
    current->next = new Node<T>();
    current->next->value = value;
}

template<class T>
void LinkedList<T>::deleteNodes(Node<T> *pNodeBefore, Node<T> *pNodeLast) {
    Node<T> *last = pNodeLast->next;
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
    Node<T> *current = pPreHead;
    while (current->next) {
        current = current->next;
    }
    current->next = pNodeBefore->next;
    pNodeBefore->next = pNodeLast->next;
    pNodeLast->next = nullptr;
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


