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

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<unordered_set<char>> rows(9);
        vector<unordered_set<char>> cols(9);
        vector<unordered_set<char>> boxes(9);

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char num = board[i][j];
                if (num == '.') continue;

                if (rows[i].find(num) != rows[i].end()) return false;
                rows[i].insert(num);

                if (cols[j].find(num) != cols[j].end()) return false;
                cols[j].insert(num);

                int boxIndex = (i / 3) * 3 + (j / 3);
                if (boxes[boxIndex].find(num) != boxes[boxIndex].end()) return false;
                boxes[boxIndex].insert(num);
            }
        }

        return true;
    }
};

// Test
int main() {
    Solution solution;

    vector<vector<char>> board1 = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                   {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                   {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                   {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                   {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                   {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                   {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                   {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                   {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    vector<vector<char>> board2 = {{'8', '3', '.', '.', '7', '.', '.', '.', '.'},
                                   {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                   {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                   {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                   {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                   {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                   {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                   {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                   {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    cout << "Output: " << (solution.isValidSudoku(board1) ? "true" : "false") << endl;
    cout << "Output: " << (solution.isValidSudoku(board2) ? "true" : "false") << endl;

    return 0;
}