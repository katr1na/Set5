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
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

bool open_file(ifstream& input, const string FILE_NAME) {
    input.open(FILE_NAME);
    if (input.fail()) {
        return false;
    }
    return true;
}

void read_file(ifstream& input, char* pMaze, const unsigned int ROWS, const unsigned int COLS, Position& startPos) {
    char c;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            input >> c;
            pMaze[i*COLS+j] = c;
            if (c == 'S') {
                startPos = Position(i, j);
            }
        }
    }
}

void print_maze(char* pMaze, const unsigned int ROWS, const unsigned int COLS) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << pMaze[i*COLS+j];
        }
        cout << endl;
    }
}

void breadth_first_search(char* pMaze, const int ROWS, const int COLS, Position& startPos) {
    bool endIsReached = false;
    bool isVisited[ROWS][COLS]; // table of visited positions
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            isVisited[i][j] = false;
        }
    }
    // create list of positions to check
    queue<Position> positionsToCheck;
    // add the starting position to list
    positionsToCheck.push(startPos);

    // while the list of positions to check is not empty
    while(!positionsToCheck.empty()) {
        // current position is the first one in list
        Position currPos = positionsToCheck.front();
        int currRow = currPos.r;
        int currCol = currPos.c;
        // remove position at front of list
        positionsToCheck.pop();
        // check if current position is equal to the end point
        if (pMaze[(currPos.r)*COLS+(currPos.c)] == 'E') {
            endIsReached = true;
            break;
        } else {
            for (int i = currRow-1; i <= currRow+1; i++) {
                if (i >= 0 && i < ROWS) {
                    // for all possible neighbors
                    // check if neighbor positions exist and are unvisited
                    if ((pMaze[i*COLS+currPos.c] == '.' || pMaze[i*COLS+currPos.c] == 'E') && !isVisited[i][currPos.c]) {
                        positionsToCheck.push(Position(i, currPos.c));
                        isVisited[i][currPos.c] = true;
                        if (pMaze[(i)*COLS+currPos.c] == '.') {
                            pMaze[(i)*COLS+currPos.c] = '@';
                        }
                    }
                }
            }
            for (int i = currCol-1; i <= currCol+1; i++) {
                if (i >= 0 && i < COLS) {
                    // for all possible neighbors
                    // check if neighbor positions exist and are unvisited
                    if ((pMaze[currPos.r*COLS+i] == '.' || pMaze[currPos.r*COLS+i] == 'E') && !isVisited[currPos.r][i]) {
                        positionsToCheck.push(Position(currPos.r, i));
                        isVisited[currPos.r][i] = true;
                        if (pMaze[currPos.r*COLS+i] == '.') {
                            pMaze[currPos.r*COLS+i] = '@';
                        }
                    }
                }
            }
        }
    }
    if (endIsReached) {
        cout << "End was reached!" << endl;
    } else {
        cout << "End cannot be reached" << endl;
    }
    print_maze(pMaze, ROWS, COLS);
}

void depth_first_search(char* pMaze, const int ROWS, const int COLS, Position& startPos) {
    bool endIsReached = false;
    bool isVisited[ROWS][COLS]; // table of visited positions
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            isVisited[i][j] = false;
        }
    }
    // create list of positions to check
    stack<Position> positionsToCheck;
    // add the starting position to list
    positionsToCheck.push(startPos);

    // while the list of positions to check is not empty
    while(!positionsToCheck.empty()) {
        // current position is the last one in list
        Position currPos = positionsToCheck.top();
        int currRow = currPos.r;
        int currCol = currPos.c;
        // remove position at back of list
        positionsToCheck.pop();
        // check if current position is equal to the end point
        if (pMaze[(currPos.r)*COLS+(currPos.c)] == 'E') {
            endIsReached = true;
            break;
        } else {
            for (int i = currRow-1; i <= currRow+1; i++) {
                if (i >= 0 && i < ROWS) {
                    // for all possible neighbors
                    // check if neighbor positions exist and are unvisited
                    if ((pMaze[i*COLS+currPos.c] == '.' || pMaze[i*COLS+currPos.c] == 'E') && !isVisited[i][currPos.c]) {
                        positionsToCheck.push(Position(i, currPos.c));
                        isVisited[i][currPos.c] = true;
                        if (pMaze[(i)*COLS+currPos.c] == '.') {
                            pMaze[(i)*COLS+currPos.c] = '@';
                        }
                    }
                }
            }
            for (int i = currCol-1; i <= currCol+1; i++) {
                if (i >= 0 && i < COLS) {
                    // for all possible neighbors
                    // check if neighbor positions exist and are unvisited
                    if ((pMaze[currPos.r*COLS+i] == '.' || pMaze[currPos.r*COLS+i] == 'E') && !isVisited[currPos.r][i]) {
                        positionsToCheck.push(Position(currPos.r, i));
                        isVisited[currPos.r][i] = true;
                        if (pMaze[currPos.r*COLS+i] == '.') {
                            pMaze[currPos.r*COLS+i] = '@';
                        }
                    }
                }
            }
        }
    }
    if (endIsReached) {
        cout << "End was reached!" << endl;
    } else {
        cout << "End cannot be reached" << endl;
    }
    print_maze(pMaze, ROWS, COLS);
}