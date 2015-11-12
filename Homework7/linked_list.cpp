//
// Created by Computer on 12.11.2015.
//

#include <stdexcept>
#include "linked_list.h"

LinkedList::Node *LinkedList::get_node(int index) {
    if (index >= size)
        throw std::out_of_range("Index out of range.");
    Node *current = head;
    for (int i = 0; i < index; i++)
        current = current->next;
    return current;
}

LinkedList *LinkedList::create_from_array(int *source, int size) {
    return nullptr;
}

LinkedList::Node *LinkedList::head_of_not_looped_list(int size) {
    return nullptr;
}

LinkedList::Node *LinkedList::head_of_looped_list_tail_with_head(int size) {
    return nullptr;
}

LinkedList::Node *LinkedList::head_of_looped_list_tail_with_index(int size, int index) {
    return nullptr;
}

bool LinkedList::is_looped(LinkedList::Node *node) {
    return false;
}

LinkedList::~LinkedList() {
    Node *node = head;
    Node *next;
    while (node) {
        next = node->next;
        delete node;
        node = next;
    }
}

int LinkedList::get_size() {
    return size;
}

int LinkedList::get(int index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    Node *node = head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    return node->value;
}

void LinkedList::add(int value) {
    if (size == 0) {
        tail = head = new Node(value);
    }
    else {
        tail->next = new Node(value);
        tail = tail->next;
    }
    size++;
}

void LinkedList::add(int index, int value) {
    if (index > size)
        throw std::out_of_range("Index out of range.");
    Node *node = new Node(value);
    if (index == 0) {
        node->next = head;
        head = node;
    }
    else {
        Node *last = head;
        for (int i = 0; i < index - 1; i++) {
            last = last->next;
        }
        node->next = last->next;
        last->next = node;
    }
    size++;
}

void LinkedList::set(int index, int value) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    Node *node = head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }
    node->value = value;
}

void LinkedList::remove(int index) {
    if (index >= size)
        throw std::out_of_range("Index out of range");
    if (index == 0) {
        head = head->next;
    }
    else {
        Node *last = head;
        for (int i = 0; i < index - 1; i++) {
            last = last->next;
        }
        Node *next = last->next->next;
        delete last->next;
        last->next = next;
    }
    size--;
}
