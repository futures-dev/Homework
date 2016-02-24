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
    // Write your code here...


    // Delete sentinel
    delete pPreHead;
}


Node<T> *LinkedList::getPreHead(void) {
    return pPreHead;
}

T &LinkedList::operator[](int i) {
    int j = 0;
    Node<T> *current = pPreHead;
    while (j < i) {
        current = current->next;
        j++;
    }
    return current->value;
}

int LinkedList::size() {
    if (pPreHead == nullptr) {
        return 0;
    }
    Node<T> *current = pPreHead;
    int j = 1;
    while (current->next) {
        current = current.next;
        j++;
    }
    return j;
}

void LinkedList::addElementToEnd(T &value) {

}

void LinkedList::deleteNodes(Node<T> *pNodeBefore, Node<T> *pNodeLast) {

}

void LinkedList::deleteNextNode(Node<T> *pNodeBefore) {

}

void LinkedList::addNodesToEnd(Node<T> *pNodeBefore, Node<T> *pNodeLast) {

}

void LinkedList::addNodeToEnd(Node<T> *pNodeBefore) {

}

void LinkedList::moveNodesAfter(Node<T> *pNode, Node<T> *pNodeBefore, Node<T> *pNodeLast) {

}

void LinkedList::moveNodeAfter(Node<T> *pNode, Node<T> *pNodeBefore) {

}


