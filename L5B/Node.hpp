#ifndef NODE_HPP
#define NODE_HPP

/**
 * @brief A single element of a linked list of given type T
 * 
 */
template<typename T>
struct Node {
    /**
     * @brief the value of this Node of given type T
     * 
     */
    T value;
    /**
     * @brief pointer to the next element of the linked list
     * 
     */
    Node<T>* pNext;
    /**
     * @brief pointer to the previous element of the linked list
     * 
     */
    Node<T>* pPrev;
};

#endif