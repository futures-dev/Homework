//
// Коломиец Андрей БПИ143
// CLion 1.1.1 MinGW 3.21
//

#include <stdexcept>
#include "linked_list.h"

/*
* Returns node at index position
*/
LinkedList::Node *LinkedList::get_node(int index) {
    if (index >= size)
        throw std::out_of_range("Index out of range.");
    Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current;
}

/*
* Returns a LinkedList with elements of the passed source array
*/
LinkedList *LinkedList::create_from_array(int *source, int size) {
    LinkedList *li = new LinkedList();
    for (int i = 0; i < size; i++) {
        li->add(source[i]);
    }
    return li;
}

/*
* Returns head of a new not looped LinkedList of exact size
*/
LinkedList::Node *LinkedList::head_of_not_looped_list(int size) {
    LinkedList *li;
    for (int i = 0; i < size; i++) {
        li->add(0);
    }
    return li->head;
}

/*
* Returns head of a new looped LinkedList of exact size. tail->next refers head
*/
LinkedList::Node *LinkedList::head_of_looped_list_tail_with_head(int size) {
    LinkedList *li;
    for (int i = 0; i < size; i++) {
        li->add(0);
    }
    li->tail->next = li->head;
    return li->head;
}

/*
* Returns head of a new looped LinkedList of exact size. tail->next refers element at index position
*/
LinkedList::Node *LinkedList::head_of_looped_list_tail_with_index(int size, int index) {
    LinkedList *li;
    for (int i = 0; i < size; i++) {
        li->add(0);
    }
    li->tail->next = li->get_node(index);
    return li->head;
}

/*
* Returns true if the list with head passed as an argument contains a loop
*/
bool LinkedList::is_looped(LinkedList::Node *node) {
    Node *slow = node;
    Node *fast1 = node;
    Node *fast2 = node;
    while (slow && (fast1 = fast2->next) && (fast2 = fast1->next)) {
        if (slow == fast1 || slow == fast2) {
            return true;
        }
        slow = slow->next;
    }
    return false;
}

/*
* LinkedList destructor
*/
LinkedList::~LinkedList() {
    Node *node = head;
    Node *next;
    while (node) {
        next = node->next;
        delete node;
        node = next;
    }
}

/*
* Returns size of the list
*/
int LinkedList::get_size() {
    return size;
}

/*
*  Returns value of the element at index position
*/
int LinkedList::get(int index) {
    return get_node(index)->value;
}

/*
* Adds a new element to the end of the list
*/
void LinkedList::add(int value) {
    if (size == 0) {
        tail = head = new Node(value);
    }
    else {
        tail->next = new Node(value);
        tail = tail->next;
    }
    if (size == 1) {
        head->next = tail;
    }
    size++;
}

/*
* Adds a new element at the specified index
*/
void LinkedList::add(int index, int value) {
    if (index > size)
        throw std::out_of_range("Index out of range.");
    if (index == size) {
        add(value);
    }
    else {
        Node *node = new Node(value);
        if (index == 0) {
            node->next = head;
            head = node;
        }
        else {
            Node *last = get_node(index - 1);
            node->next = last->next;
            last->next = node;
        }
    size++;
    }
}

/*
* Sets new value to the element at the specified index
*/
void LinkedList::set(int index, int value) {
    get_node(index)->value = value;
}

/*
* Removes the element at the specified index
*/
void LinkedList::remove(int index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    if (index == 0) {
        Node *next = head->next;
        delete head;
        head = next;
    }
    else {
        Node *last = get_node(index - 1);
        Node *next = last->next->next;
        delete last->next;
        last->next = next;
    }
    size--;
}
