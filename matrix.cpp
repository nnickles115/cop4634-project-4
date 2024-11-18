#include <chrono>
#include <iostream>

/**
 * @file matrix.cpp
 * @brief This program creates a large global array and performs read and write
 * operations on it to determine the effects on virtual memory.
 * 
 * @author Noah Nickles
 * @author Dylan Stephens
 * @date 11/18/2024
 * @details Course COP4634
 */

/*** CONSTANTS ***/
const int ROWS = 20480;
const int COLS = 4096;

/*** GLOBALS ***/
char matrix[ROWS][COLS];

/*** MATRIX OPERATIONS ***/

/**
 * Writes to matrix by row-major.
 */
void writeRow() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            matrix[i][j] = 'R';
        }
    }
}

/**
 * Writes to matrix by col-major.
 */
void writeCol() {
    for(int j = 0; j < COLS; j++) {
        for(int i = 0; i < ROWS; i++) {
            matrix[i][j] = 'C';
        }
    }
}

/**
 * Reads from matrix by row-major.
 */
void readRow() {
    volatile char temp; // Prevent compiler optimization with 'volatile'
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            temp = matrix[i][j];
        }
    }
}

/**
 * Reads from matrix by col-major.
 */
void readCol() {
    volatile char temp; // Prevent compiler optimization with 'volatile'
    for(int j = 0; j < COLS; j++) {
        for(int i = 0; i < ROWS; i++) {
            temp = matrix[i][j];
        }
    }
}

/*** MAIN ***/

/**
 * Measures times of read/write operations and prints the average.
 * 
 * @param void Function pointer
 * @param operation Name of the operation
 */
void measure(void (*func)(), const std::string &operation) {
    const int repetitions = 10;
    auto start = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < repetitions; i++) {
        func();
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << operation 
              << " Average Time: " 
              << (elapsed.count() / repetitions)
              << " seconds"
              << std::endl;
}

/**
 * Prints error messages to cerr to detail proper program execution arguments.
 */
void printErrors() {
    std::cerr << "Error: Please specify an operation number (1-4) as a command line argument.\n";
    std::cerr << "1: Write Row-Major\n";
    std::cerr << "2: Write Col-Major\n";
    std::cerr << "3: Read Row-Major\n";
    std::cerr << "4: Read Col-Major\n";
}

/**
 * Main method.
 * Reads in a flag (1-4) and selects the matrix operation to execute
 * and measure the times.
 */
int main(int argc, char** argv) {
    if(argc < 2) {
        std::cerr << "Usage: ./matrix <operation>\n";
        printErrors();
        return 1;
    }

    int operation = std::stoi(argv[1]);
    switch(operation) {
        case 1:
            measure(writeRow, "Write Row-Major");
            break;
        case 2:
            measure(writeCol, "Write Col-Major");
            break;
        case 3:
            measure(readRow, "Read Row-Major");
            break;
        case 4:
            measure(readCol, "Read Col-Major");
            break;
        default:
            printErrors();
            return 1;
    }
    return 0;
}