// Description: https://leetcode.com/problems/valid-sudoku/description/

/*
    Approach: Hash Set

    Use three sets of hash sets to track seen numbers: rows, columns, and 3x3 boxes.
    Iterate through each cell of the 9x9 board once.
    Skip empty cells (marked with '.').
    For each number, check if it exists in the corresponding row, column, or box set.
    Calculate box index using formula: (row/3) * 3 + (col/3).
    If duplicate found in any set, return false. Otherwise, add to all three sets.

    Time complexity: O(1) - Board size is fixed at 9x9 = 81 cells.
    Space complexity: O(1) - Fixed number of sets for 9 rows, columns, and boxes.
*/

import java.util.*;

class Solution {
    public boolean isValidSudoku(char[][] board) {
        Set<Character>[] rows = new HashSet[9];
        Set<Character>[] cols = new HashSet[9];
        Set<Character>[] boxes = new HashSet[9];

        for (int i = 0; i < 9; i++) {
            rows[i] = new HashSet<>();
            cols[i] = new HashSet<>();
            boxes[i] = new HashSet<>();
        }

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char num = board[i][j];
                if (num == '.') continue;

                if (rows[i].contains(num)) return false;
                rows[i].add(num);

                if (cols[j].contains(num)) return false;
                cols[j].add(num);

                int boxIndex = (i / 3) * 3 + (j / 3);
                if (boxes[boxIndex].contains(num)) return false;
                boxes[boxIndex].add(num);
            }
        }

        return true;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        char[][] board1 = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                           {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                           {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                           {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                           {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                           {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                           {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                           {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                           {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

        char[][] board2 = {{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                           {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                           {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                           {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                           {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                           {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                           {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                           {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                           {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

        System.out.println("Output: " + solution.isValidSudoku(board1));
        System.out.println("Output: " + solution.isValidSudoku(board2));
    }
}
