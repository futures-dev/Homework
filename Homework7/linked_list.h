#ifndef LIST_PROJECT_LINKEDLIST_H
#define LIST_PROJECT_LINKEDLIST_H

/**
 * Class that represents LinkedList data structure for storing integer elements
 * (consider that this collection does not use C++ templates, so you can store
 * only integers in this collection).
 *
 * Note that current implementation is NOT a doubly linked list. So each node
 * have only pointer to next element and next element doesn't know anything
 * about previous one.
 *
 * You need to implement current class and all its static functions.
 *
 * Consider that all non-static functions of current class are dedicated to
 * the data structure implementation and how it behaves during usage.
 *
 * There are also 3 static functions here that represent *static factories*.
 * Such methods are pretty useful to create instances of the class easily,
 * when it is not so convenient to use constructor instead.
 * They also can use private members of current class, where they are defined,
 * which will makes them extremely useful in some cases.
 * (In your assignment, you might want to use private members in static functions
 * so consider this a bit hint :) )
 *
 * There is also a static function "is_looped" which detects if passed linked
 * list is looped or not. Declaring this function in current class will allow
 * you to use private members which is essential to do solve this problem.
 *
 * As always, you need to implement this class in "linked_list.cpp" file and you MUST NOT
 * change "linked_list.h" file.
 */
class LinkedList {
private:
    /**
     * Class of the Node element that are need to be stored in the linked list.
     * You don't need to implement anything here.
     *
     * Disclaimer: you can see here that all members of the class are public which is
     * not always good way to do it. Since we assume that Node class is used in LinkedList
     * class only and not exposed to user, we can safely design it with public members for
     * simplicity.
    */
    class Node {
    public:
        /** Pointer to next element */
        Node *next = nullptr;

        /** Integer value that is stored in current node */
        int value;

        /**
         * Constructor of the node element
         *
         * Parameters:
         *  int value - value of the element.
         */
        Node(int value) : value(value) { }

        /**
         * Destructor of the node element.
         */
        ~Node() {
            next = nullptr;
        }
    };

    /* First element of the linked list. If it equals to nullptr then there are no elements in the list. */
    Node *head = nullptr;

    /* Last element of the linked list. If it equals to nullptr then there are no elements in the list. */
    Node *tail = nullptr;

    /* Number of elements in current linked list */
    int size = 0;

    /**
     * Getting node element of the list with specified index
     *
     * Parameters:
     *  int index - index of the node in the list. Non-negative integer value.
     *
     * Returns:
     *  list node at current index
     */
    Node *get_node(int index);

public:

    /**
     * Here we have a section of static factory methods, see
     * some information about such functions in the explanation
     * above.
     */

    /**
     * Static factory function to create linked list filled with
     * items from specified array.
     *
     * Parameters:
     *  int* source - array to be a source of elements that are need to be stored
     *                in created linked list.
     *  int size    - number of elements that are need to be stored in linked list
     *                from index 0 (inclusively). Strictly positive value.
     *
     * Returns:
     *  new linked list object pointer with is filled of "size" items from "source"
     */
    static LinkedList *create_from_array(int *source, int size);

    /**
     * Method to create a linked list with specified size and returning the head of it.
     *
     * You are not forced to create a LinkedList object because only Node class is needed.
     *
     * The values that are associated with Node objects does not matter, this function
     * is used only for is_looped function usage.
     *
     * Do not worry about the memory deallocation of created list, since you have no access
     * to Node class. This is a gap of current template, but such design is just for educational
     * purposes.
     *
     * Parameters:
     *  int size - number of Node elements to be created in the list. Strictly positive value.
     *
     * Returns:
     *  head element of the created list.
     */
    static Node *head_of_not_looped_list(int size);

    /**
     * Method to create a linked list with specified size, loop its tail with the head as next
     * element and return the head.
     *
     * You are not forced to create a LinkedList object because only Node class is needed.
     *
     * The values that are associated with Node objects does not matter, this function
     * is used only for is_looped function usage.
     *
     * Do not worry about of the memory deallocation of created list, since you have no access
     * to Node class. This is a gap of current template, but such design is just for educational
     * purposes.
     *
     * Parameters:
     *  int size - number of Node elements to be created in the list. Strictly positive value.
     *
     * Returns:
     *  head element of the created list.
     */
    static Node *head_of_looped_list_tail_with_head(int size);

    /**
     * Method to create a linked list with specified size, loop its tail with the specified
     * element as next element and return the head.
     *
     * You are not forced to create a LinkedList object because only Node class is needed.
     *
     * The values that are associated with Node objects does not matter, this function
     * is used only for is_looped function usage.
     *
     * Do not worry about of the memory deallocation of created list, since you have no access
     * to Node class. This is a gap of current template, but such design is just for educational
     * purposes.
     *
     * Parameters:
     *  int size  - number of Node elements to be created in the list. Strictly positive value.
     *  int index - index of the Node element in the list which should be considered as next
     *              element for the tail of the list. Non-negative value, less than "size".
     *
     * Returns:
     *  head element of the created list.
     */
    static Node *head_of_looped_list_tail_with_index(int size, int index);

    /**
     * Function to understand if LinkedList which is represented with Node class object
     * is looped or not.
     * Values that are associated with Node elements does not matter, since we search only
     * for the fact of the loop in the list.
     *
     * Returns:
     *  true - if list is looped, false - otherwise
     */
    static bool is_looped(Node *node);

    /**
     * Destructor of the list.
     */
    virtual ~LinkedList();

    /**
     * Returning size of the list, i.e. number of elements in the list.
     *
     * Returns:
     *  non-negative number of the elements in the list.
     */
    int get_size();

    /**
     * Getting integer element of the list with specified index
     *
     * Parameters:
     *  int index - index of element of the list, which needs to be returned. Non-negative integer value.
     *
     * Returns:
     *  value of the element with index of current list
     *
     * Throws:
     *  out_of_range - if index is not within bounds [0, size - 1].
     */
    int get(int index);

    /**
     * Adding an element to the end of the list.
     *
     * Parameters:
     *  int value - value that is needed to be stored in the list.
     */
    void add(int value);

    /**
     * Adding an element to the specified index of the list.
     * I.e. after execution the element should be at index which equals to
     * "index" parameter. All indexes less than "index" should remain
     * unchanged, and all indices equals to "index" and greater should
     * incremented by 1.
     *
     * Parameters:
     *  int index - index of element of the list, where a new element should be placed.
     *              Non-negative integer value.
     *  int value - value that is needed to be stored in the list.
     *
     * Throws:
     *  out_of_range - if index is not within bounds [0, size - 1].
     */
    void add(int index, int value);

    /**
     * Setting the element of the list with specified value.
     *
     * Parameters:
     *  int index - index of element of the list, which needs to be set. Non-negative integer value.
     *  int value - value that is needed to be stored in the list.
     *
     * Throws:
     *  out_of_range - if index is not within bounds [0, size - 1].
     */
    void set(int index, int value);

    /**
     * Removing the specified element from the list.
     *
     * Parameters:
     *  int index - index of element of the list, which needs to be removed. Non-negative integer value.
     *
     * Throws:
     *  out_of_range - if index is not within bounds [0, size - 1].
     */
    void remove(int index);
};


#endif //LIST_PROJECT_LINKEDLIST_H