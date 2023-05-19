/* CSCI 200: Lab 5B: 5B - Recursion II: Merge Sort
 *
 * Author: Katrina Ngo
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Implement a Merge Sort algorithm on Linked Lists
 */

#include "LinkedList.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
    LinkedList<int>* list1 = new LinkedList<int>;
    list1->insert(0, 4);
    list1->insert(1, 3);
    list1->insert(2, 8);
    list1->insert(3, 1);
    list1->insert(4, 5);
    list1->insert(5, 9);
    list1->insert(6, 7);
    list1->insert(7, 2);
    list1->insert(8, 6);

    cout << "List 1: ";
    for (int i = 0; i < list1->size(); i++) {
        cout << list1->get(i) << " ";
    }
    cout << endl;
    list1->mergeSort();
    for (int i = 0; i < list1->size(); i++) {
        cout << list1->get(i) << " ";
    }
    cout << endl;

    return 0;
}