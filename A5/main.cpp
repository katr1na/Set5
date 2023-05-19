/* CSCI 200: Assignment 5: A5 - a-MAZE-ing
 *
 * Author: Katrina Ngo
 * Resources used (Office Hours, Tutoring, Other Students, etc & in what capacity):
 *     // list here any outside assistance you used/received while following the
 *     // CS@Mines Collaboration Policy and the Mines Academic Code of Honor
 *
 * Implement a breadth-first-search and a depth-first-search on various mazes to reach the endpoint
 */

#include "maze_functions.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // check program was started correctly
    string filename;
    if(argc != 2) {
        // prompt user for file name if one isn't provided in command line argument
        cout << "Input file name to open: ";
        cin >> filename;
    } else {
        // get filename to open
        cout << "Opening file \"" << argv[1] << "\"" << endl;
        filename = argv[1];
    }
    
    // open file for parsing
    ifstream fileIn;
    if( !open_file(fileIn, filename) ) {
        cerr << "Could not open file \"" << filename << "\"" << endl;
        cerr << "Shutting down" << endl;
        return -1;
    } else {
        cout << "File opened successfully!" << endl << endl;
    }

    // create 2D array of maze and read in characters from file
    int rows;
    int cols;
    fileIn >> rows >> cols;
    char mazeChars[rows][cols];
    Position startPos;
    read_file(fileIn, &mazeChars[0][0], rows, cols, startPos);

    // prompt user to search maze via BFS or DFS
    int choice;
    cout << "Enter 1 to search via BFS." << endl << "Enter 2 to search via DFS." << endl << "Choice: ";
    cin >> choice;
    if (choice == 1) {
        breadth_first_search(&mazeChars[0][0], rows, cols, startPos);
    } else if (choice == 2) {
        depth_first_search(&mazeChars[0][0], rows, cols, startPos);
    }

    fileIn.close();
    return 0;
}