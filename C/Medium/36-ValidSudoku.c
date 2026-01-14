// Description: https://leetcode.com/problems/valid-sudoku/description/

/*
    Approach: Hash Set (using arrays)

    Use three arrays of bitmasks to track seen numbers: rows, columns, and 3x3 boxes.
    Iterate through each cell of the 9x9 board once.
    Skip empty cells (marked with '.').
    For each number, check if it exists in the corresponding row, column, or box.
    Calculate box index using formula: (row/3) * 3 + (col/3).
    If duplicate found in any set, return false. Otherwise, mark as seen.

    Time complexity: O(1) - Board size is fixed at 9x9 = 81 cells.
    Space complexity: O(1) - Fixed arrays for 9 rows, columns, and boxes.
*/

#include <stdbool.h>
#include <stdio.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    int rows[9] = {0};
    int cols[9] = {0};
    int boxes[9] = {0};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c = board[i][j];
            if (c == '.') continue;

            int num = c - '1';  // Convert '1'-'9' to 0-8
            int mask = 1 << num;
            int boxIndex = (i / 3) * 3 + (j / 3);

            // Check if number already exists
            if (rows[i] & mask) return false;
            if (cols[j] & mask) return false;
            if (boxes[boxIndex] & mask) return false;

            // Mark as seen
            rows[i] |= mask;
            cols[j] |= mask;
            boxes[boxIndex] |= mask;
        }
    }

    return true;
}

// Test
int main() {
    // Example 1: Valid sudoku board
    char* board1[] = {
        "53..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };
    int colSize1 = 9;
    printf("Output: %s\n", isValidSudoku(board1, 9, &colSize1) ? "true" : "false");

    // Example 2: Invalid sudoku (duplicate 8 in first column)
    char* board2[] = {
        "83..7....",
        "6..195...",
        ".98....6.",
        "8...6...3",
        "4..8.3..1",
        "7...2...6",
        ".6....28.",
        "...419..5",
        "....8..79"
    };
    int colSize2 = 9;
    printf("Output: %s\n", isValidSudoku(board2, 9, &colSize2) ? "true" : "false");

    return 0;
}
