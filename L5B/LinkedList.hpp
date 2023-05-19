#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include <exception>
#include <iostream>

template<typename T>
class LinkedList {
    public:
    /**
     * @brief Construct a new Linked List object
     * 
     */
    LinkedList();
    /**
     * @brief Copy Constructor that performs a deep copy of the other list
     * 
     * @param OTHER 
     */
    LinkedList(const LinkedList<T>& OTHER);
    /**
     * @brief Copy Assignment Operator that deallocates the existent list (if any) 
     * then performs a deep copy of the other list
     * 
     * @param OTHER 
     * @return LinkedList& 
     */
    LinkedList& operator=(const LinkedList<T>& OTHER);
    /**
     * @brief if POS exists, returns the value at that position. 
     * Otherwise, throws std::out_of_range exception
     * 
     * @param POS 
     * @return T 
     */
    /**
     * @brief destroys the existing list by removing all nodes that are present in the list
     * 
    */
    ~LinkedList();
    /**
     * @brief eturns the value of the element at given position. 
     * If position doesn't exist, throws a std::out_of_range exception
     * 
     * @param POS 
     * @return T 
     */
    T get(const int POS) const;
    /**
     * @brief if POS exists, sets the value at that position. 
     * Otherwise, does nothing
     * 
     * @param POS 
     * @param VAL 
     */
    void set(const int POS, const T VAL);
    /**
     * @brief inserts a node before the given POS. If POS is negative, inserts at the beginning of the list. 
     * If POS is greater than the current size, inserts at the end of the list. 
     * Updates head, tail, and size as appropriate
     * 
     * @param POS 
     * @param VAL 
     */
    void insert(const int POS, const T VAL);
    /**
     * @brief if the provided position exists in the list, removes and deallocates the associated node. 
     * If the provided position is out of range for the current list, 
     * then clamp the position to the head or tail of the list as appropriate. If the list is empty, then do nothing
     * 
     * @param POS 
     */
    void remove(const int POS);
    /**
     * @brief returns the max value within the list. 
     * Otherwise, throws std::out_of_range exception
     * 
     * @return T 
     */
    T max() const;
    /**
     * @brief returns the min value within the list. 
     * Otherwise, throws std::out_of_range exception
     * 
     * @return T 
     */
    T min() const;
    /**
     * @brief returns the position of the first occurrence of the target. 
     * If target doesn't exist, returns -1
     * 
     * @param TARGET 
     * @return int 
     */
    int find(const T TARGET) const;
    /**
     * @brief returns the current number of nodes within the list
     * 
     * @return unsigned int 
     */
    unsigned int size() const;
    /**
     * @brief performs mergesort on list
     * 
     */
    void mergeSort();

    private:
    Node<T>* mpHead; // pointer to the head node of the list
    Node<T>* mpTail; // pointer to the tail node of the list
    unsigned int mSize; // stores the current number of nodes in the list
    /**
     * @brief creates a node with provided value and null next pointer
     * 
     * @param VALUE 
     * @return Node<T>* 
     */
    Node<T>* mMakeNodeForValue(const T VALUE);
    /**
     * @brief splits current list in half and assigns pLeft and pRight to respective halves
     * 
     * @param pLeft 
     * @param pRight 
     */
    void mSplitList(LinkedList<T>*& pLeft, LinkedList<T>*& pRight);
    /**
     * @brief merges pLeft and pRight into one list, sorted
     * 
     * @param pLeft 
     * @param pRight 
     */
    void mMergeLists(LinkedList<T>*& pLeft, LinkedList<T>*& pRight);
};

// FUNCTION IMPLEMENTATIONS

template<typename T>
LinkedList<T>::LinkedList() {
    mpHead = nullptr;
    mpTail = nullptr;
    mSize = 0;
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& OTHER){
    mpHead = nullptr;
    mpTail = nullptr;
    mSize = 0;
    for (int i = 0; i < OTHER.size(); i++) {
        insert(i, OTHER.get(i));
    }
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& OTHER) {
    if (this != &OTHER) {
        // delete existing list
        for (int i = 0; i < mSize; i++) {
            Node<T>* nodeToDelete = mpHead;
            mpHead = mpHead->pNext;
            mpHead->pPrev = nullptr;
            delete[] nodeToDelete;
        }
    }
    mpHead = nullptr;
    mpTail = nullptr;
    mSize = 0;
    for (int i = 0; i < OTHER.size(); i++) {
        insert(i, OTHER.get(i));
    }
    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    for (int i = 0; i < mSize; i++) {
        Node<T>* nodeToDelete = mpHead;
        mpHead = mpHead->pNext;
        delete nodeToDelete;
    }
    mpHead = nullptr;
    mpTail = nullptr;
    mSize = 0;
}

template<typename T>
T LinkedList<T>::get(const int POS) const {
    int counter = 0;
    Node<T>* currNode = mpHead;
    while (counter < POS && currNode != nullptr) {
        counter++;
        currNode = currNode->pNext;
    }
    if (currNode != nullptr && POS >= 0) {
        return currNode->value;
    } else {
        throw std::out_of_range("position is out of range");
    }
}

template<typename T>
void LinkedList<T>::set(const int POS, const T VAL) {
    // if trying to set an invalid spot, or list is empty - do nothing
    if (POS >= 0) {
        Node<T>* pCurrNode = mpHead;
        int counter = 0;
    // advance through list counting number of jumps and continue until position found or at end
        while (counter < POS && pCurrNode != nullptr) {
            counter++;
            pCurrNode = pCurrNode->pNext;
        }
    // if valid position, change value
        if (pCurrNode != nullptr) {
            pCurrNode->value = VAL;
        }
    }   
}

template<typename T>
void LinkedList<T>::insert(const int POS, const T VAL) {
    // if position is before the beginning, add to front
    if(POS <= 0 || mpHead == nullptr) {
        // make a new node
        Node<T>* pNewNode = mMakeNodeForValue(VAL);      
        // if list is initially empty
        if (mpHead == nullptr) {
            // head and tail are the new node                       
            mpHead = pNewNode;
            mpTail = pNewNode;
        } else {
        // otherwise, chain into existing node
            // link new node and head, update head
            pNewNode->pNext = mpHead;
            mpHead->pPrev = pNewNode;
            mpHead = pNewNode;
        }
    } else {
        Node<T>* pCurrNode = mpHead;
        int counter = 0;
        // advance through list counting number of jumps and continue until position found or at end
        while (counter < POS && pCurrNode != nullptr) {
            counter++;
            pCurrNode = pCurrNode->pNext;
        }
        // if we have gone past the end
        if(pCurrNode == nullptr) {
            // add to back
            // make new node
            Node<T>* pNewNode = mMakeNodeForValue(VAL);
            // if list is initially empty
            if (mpHead == nullptr) {
                // head and tail are the new node                       
                mpHead = pNewNode;
                mpTail = pNewNode;
            } else {
                // otherwise, chain off existing node
                // link new node and tail, update tail
                pNewNode->pNext = nullptr;
                pNewNode->pPrev = mpTail;
                mpTail->pNext = pNewNode;
                mpTail = pNewNode;
            }
        } else {
            // otherwise add before target position
            Node<T>* pNewNode = mMakeNodeForValue(VAL);
            pNewNode->pNext = pCurrNode;
            pNewNode->pPrev = pCurrNode->pPrev;
            pCurrNode->pPrev = pNewNode;
            pNewNode->pPrev->pNext = pNewNode;
        }
    }
    mSize++;
}

template<typename T>
void LinkedList<T>::remove(const int POS) {
    // if list is empty
    if(mpHead == nullptr) {
        // do nothing
        return;
    } 
    // if position is before start of list
    else if(POS <= 0) {
        // remove from front
        // if list is empty - do nothing
        if(mpHead == nullptr) return;                
        // store pointer to current head
        Node<T>* pNodeToDelete = mpHead;
        // advance head
        mpHead = mpHead->pNext;
        // if we're now pointing at nothing, list only had one element
        if (mpHead == nullptr) {
            //  set tail to also be null so it points to nothing
            mpTail = nullptr;
        } else {
            // otherwise, list still has elements
            // set back pointer to be null
            mpHead->pPrev = nullptr;
        }
        // delete former head
        delete pNodeToDelete;
    } else {
        Node<T>* pCurrNode = mpHead;
        int counter = 0;
        // advance through list counting number of jumps and continue until position found or at end
         while (counter < POS-1 && pCurrNode != nullptr) {
            counter++;
            pCurrNode = pCurrNode->pNext;
        }
        // if we have gone to tail or further
        if(pCurrNode == nullptr || pCurrNode == mpTail) {
            // remove from back
            // if list is empty, do nothing
            if(mpTail == nullptr) return;
            // store pointer to current tail
            Node<T>* pNodeToDelete = mpTail;
            // move tail backwards
            mpTail = mpTail->pPrev;
            // if we're now pointing at nothing, list only had one element
            if (mpTail == nullptr) {
                //  set head to also be null so it points to nothing
                mpHead = nullptr;
            } else {
            // otherwise, list still has elements
                // set next pointer to be null
                mpTail->pNext = nullptr;
            }
            // delete former tail
            delete pNodeToDelete;
        } else {
            // unlink current node
            Node<T>* nodeToDelete = pCurrNode->pNext;
            pCurrNode->pNext = pCurrNode->pNext->pNext;
            if (pCurrNode->pNext == nullptr) {
                mpTail = pCurrNode;
            } else {
                pCurrNode->pNext->pPrev = pCurrNode;
            }
            // delete current node
            delete nodeToDelete;
        }
    }
    mSize--;
}

template<typename T>
T LinkedList<T>::max() const {
    const Node<T>* pCURR_NODE = mpHead;
    // if list is empty
    if(pCURR_NODE == nullptr) {
        // throw exception
        throw std::out_of_range("list is empty");
    }
    // traverse list tracking max value present
    int maxVal = pCURR_NODE->value;
    while (pCURR_NODE != nullptr) {
        if (pCURR_NODE->value > maxVal) {
            maxVal = pCURR_NODE->value;
        }
        pCURR_NODE = pCURR_NODE->pNext;
    }
    return maxVal;
}

template<typename T>
T LinkedList<T>::min() const {
    const Node<T>* pCURR_NODE = mpHead;
    // if list is empty
    if(pCURR_NODE == nullptr) {
        // throw exception
        throw std::out_of_range("list is empty");
    }
    // traverse list tracking min value present
    int minVal = pCURR_NODE->value;
    while (pCURR_NODE != nullptr) {
        if (pCURR_NODE->value < minVal) {
            minVal = pCURR_NODE->value;
        }
        pCURR_NODE = pCURR_NODE->pNext;
    }
    return minVal;
}

template<typename T>
int LinkedList<T>::find(const T TARGET) const {
    const Node<T>* pCURR_NODE = mpHead;
    int counter = -1;
    // advance through list until end and target is found or end reached
    bool found = false;
    while (!found && pCURR_NODE != nullptr) {
        if (pCURR_NODE->value == TARGET) {
            found = true;
        }
        pCURR_NODE = pCURR_NODE->pNext;
        counter++;
    }
    // return found position or -1 if end of list reached
    if (!found) {
        return -1;
    }
    return counter;
}

template<typename T>
Node<T>* LinkedList<T>::mMakeNodeForValue(const T VALUE) {
    Node<T>* newNode = new Node<T>;
    newNode->value = VALUE;
    newNode->pPrev = nullptr;
    newNode->pNext = nullptr;
    return newNode;
}

template<typename T>
unsigned int LinkedList<T>::size() const {
    return mSize;
}

template<typename T>
void LinkedList<T>::mergeSort() {
    // base case
    if(mSize <= 1) {return;} // already sorted
    // divide & split
    LinkedList<T> *pLeft, *pRight;
    mSplitList(pLeft, pRight);
    // callee now empty, pLeft & pRight hold both halves
    // recurse
    pLeft->mergeSort();
    pRight->mergeSort();
    // conquer & merge
    mMergeLists(pLeft, pRight);
    // callee now sorted, pLeft & pRight empty
}

template<typename T>
void LinkedList<T>::mSplitList(LinkedList<T>*& pLeft, LinkedList<T>*& pRight) {
    pLeft = new LinkedList<T>;
    // create left half of list
    for (int i = 0; i < mSize/2; i++) {
        pLeft->insert(i, get(i));
    }
    // create right half of list
    pRight = new LinkedList<T>;
    for (int i = mSize/2; i < mSize; i++) {
        pRight->insert(i, get(i));
    }
    // remove all elements in original list to get an empty list
    while (mSize > 0) {
        remove(0);
    }
}

template<typename T>
void LinkedList<T>::mMergeLists(LinkedList<T>*& pLeft, LinkedList<T>*& pRight)  {
    int rightIndex = 0;
    int leftIndex = 0;
    int indexOfMergedArray = 0; // index of merged list
    while (leftIndex < pLeft->size() && rightIndex < pRight->size()) {
        // if current element in left list is less than current element in right list
        if (pLeft->get(leftIndex) <= pRight->get(rightIndex)) {
            insert(indexOfMergedArray, pLeft->get(leftIndex)); // add left element to merged list
            leftIndex++; // increment left index
        } else {
            insert(indexOfMergedArray, pRight->get(rightIndex)); // otherwise, add right element to merged list
            rightIndex++; // increment right index
        }
        indexOfMergedArray++; // increment merged list index
    }
    // if there are any elements left in left list, add them to merged list
    while (leftIndex < pLeft->size()) {
        insert(indexOfMergedArray, pLeft->get(leftIndex)); 
        leftIndex++;
        indexOfMergedArray++;
    }
    // if there are any elements left in right list, add them to merged list
    while (rightIndex < pRight->size()) {
        insert(indexOfMergedArray, pRight->get(rightIndex));
        rightIndex++;
        indexOfMergedArray++;
    }
    // delete left and right lists
    delete pLeft;
    delete pRight;
}
#endif