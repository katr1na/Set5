#ifndef MAZE_FUNCTIONS_H
#define MAZE_FUNCTIONS_H

#include "Position.h"
#include <string>

/**
 * @brief Open the input file stream for the corresponding filename. 
 * Check that the file opened correctly. The string filename will remain unchanged.
 * 
 * @param input 
 * @param FILE_NAME 
 * @return true 
 * @return false 
 */
bool open_file(std::ifstream& input, const std::string FILE_NAME);

/**
 * @brief Read in all the characters of the maze that are in the file stream
 * 
 * @param input 
 * @param pMaze 
 * @param ROWS 
 * @param COLS 
 * @param startPos 
 */
void read_file(std::ifstream& input, char* pMaze, const unsigned int ROWS, const unsigned int COLS, Position& startPos);

/**
 * @brief Print current state of maze
 * 
 * @param pMaze 
 * @param ROWS 
 * @param COLS 
 */
void print_maze(char* pMaze, const unsigned int ROWS, const unsigned int COLS);

/**
 * @brief Perform breadth-first-search on given maze
 * 
 * @param pMaze 
 * @param ROWS 
 * @param COLS 
 * @param startPos 
 */
void breadth_first_search(char* pMaze, const int ROWS, const int COLS, Position& startPos);

/**
 * @brief Perform depth-first-search on given maze
 * 
 * @param pMaze 
 * @param ROWS 
 * @param COLS 
 * @param startPos 
 */
void depth_first_search(char* pMaze, const int ROWS, const int COLS, Position& startPos);

#endif