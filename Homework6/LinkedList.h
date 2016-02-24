#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*
   Node class that wraps the element in the LinkedList.
   Next reference is 0 when there is no next value after this node.
   */
template<class T>
class Node {
public:
    T value;
    // The content/data/value of the node

    Node *next;
    // The pointer to the next element
public:
    Node() : next(nullptr) { }
    //Constructor
};

/* Linked list template */
template<class T>
class LinkedList {
private:
    Node<T> *pPreHead;
    // Вспомогательный элемент

public:
    LinkedList(void);

    ~LinkedList(void);

    Node<T> *getPreHead(void);

    /*
     * Возвращает pPreHead
     */

    T &operator[](int i);

    /*
     * Возвращает элемент по индексу
     */

    int size();

    /*
     * Вернуть размер списка
     */

    void addElementToEnd(T &value);

    /*
     * Добавить новый узел со значением value в конец списка
     */

    void deleteNodes(Node<T> *pNodeBefore, Node<T> *pNodeLast);

    /*
     * Удалить узлы начиная от pNodeBefore->next и до узла pNodeLast
     * Важно!!! Не удалять pNodeBefore, а pNodeLast удалить
     * т.е. удалить узлы от pNodeBefore->next до pNodeLast включительно.
     */

    void deleteNextNode(Node<T> *pNodeBefore);

    /*
     * Удалить узел pNodeBefore->next
     * Важно!!! Не удалять pNodeBefore
     */

    void addNodesToEnd(Node<T> *pNodeBefore, Node<T> *pNodeLast);

    /*
     * Добавить в конец текущего списка узлы из другого списка от pNodeBefore->next до pNodeLast
     * Важно!!! pNodeBefore и pNodeLast - узлы другого списка
     * Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
     */

    void addNodeToEnd(Node<T> *pNodeBefore);

    /*
     * Добавить в конец текущего списка узел pNodeBefore->next из другого списка
     * Важно!!! pNodeBefore - узел другого списка
     * Из другого списка узел pNodeBefore->next исчезают.
     */

    void moveNodesAfter(Node<T> *pNode, Node<T> *pNodeBefore, Node<T> *pNodeLast);

    /*
     * Вставить из другого списка узлы pNodeBefore->next ... pNodeLast
     * в текущий список после узла pNode.
     * Важно!!! pNodeBefore и pNodeLast - узлы другого списка
     * Из другого списка узлы pNodeBefore->next...pNodeLast исчезают.
     */

    void moveNodeAfter(Node<T> *pNode, Node<T> *pNodeBefore);
    /*
     * Вставить из другого списка узел pNodeBefore->next
     * в текущий список после узла pNode.
     * Важно!!! pNodeBefore - узел другого списка
     * Из другого списка узел pNodeBefore->next исчезает.
     */
};

#include "LinkedList.hpp"

#endif
