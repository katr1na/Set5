/* CSCI 200: Lab 5C: 5C - A Needle in the Haystack
 *
 * Author: Katrina Ngo
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Implement a Binary search on a sorted list generated with random integers
 * by prompting user for size, min, max, and targets of list
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void selection_sort(int list[], const int SIZE) {
    // sort list in ascending order
    // for every element in list
    for (int i = 0; i < SIZE; i ++) {
        int k = i;
        // look through list for smallest element
        for (int j = i+1; j < SIZE; j++) {
            if (list[j] < list[k]) {
                k = j;
            }
        }
        // swap smallest element with current element
        int temp = list[k];
        list[k] = list[i];
        list[i] = temp;
    }
}

void binary_search(int list[], const int SIZE, const int TARGET) {
    bool found = false;
    int low = 0;
    int high = SIZE - 1;
    int pos = 0;
    // while target hasn't been found and low position of list is less than or equal to high position of list
    while (low <= high && !found) {
        pos = (low+high)/2;
        // check if target is equal to middle element of current section we're searching
        if (list[pos] == TARGET) {
            found = true;
        } else if (list[pos] < TARGET) {
            // if middle element is less than target, search in right half of list
            low = pos + 1;
        } else {
            // if middle element is greater than target, search in left half of list
            high = pos - 1;
        }
    }
    // print position of target if found, otherwise print -1
    if (found) {
        cout << "Target found at position " << pos << endl;
    } else {
        cout << "-1" << endl;
    }
}

int main() {
    srand(time(0));
    int n;
    int numTargets;
    int target;
    int min;
    int max;
    cout << "Input size of list: ";
    cin >> n;
    cout << "Input min of list: ";
    cin >> min;
    cout << "Input max of list: ";
    cin >> max;
    cout << "Input number of targets to search for: ";
    cin >> numTargets;

    // generate random values between min and max inclusive
    int list[10*n];
    for (int i = 0; i < 10*n; i++) {
        list[i] = rand() % (max-min+1) + min;
    }
    for (int i = 0; i < 10*n; i++) {
        cout << list[i] << " ";
    }
    cout << endl;
    selection_sort(list, 10*n); // sort list
    for (int i = 0; i < 10*n; i++) {
        cout << list[i] << " ";
    }
    cout << endl;

    // for each number of targets user wants to search for, perform binary search
    for (int i = 0; i < numTargets; i++) {
        cout << "Input target to search for: ";
        cin >> target;
        binary_search(list, 10*n, target);
    }
}