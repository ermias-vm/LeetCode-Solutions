#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;


// Description:  https://leetcode.com/problems/valid-sudoku/

//  Approach 1 : Using unordered_set

/* 
    Time complexity: O(1) - The board is always 9x9, so the time complexity is constant.
    Space complexity: O(1) - We use a fixed amount of extra space for the sets.

    This approach uses three sets to keep track of the numbers seen in each row, column, and 3x3 subgrid.
    We iterate through each cell in the board and check if the current number has already been seen in the corresponding row, column, or subgrid.
    If it has, the board is not a valid Sudoku. If we finish the iteration without finding any duplicates, the board is valid.
*/


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

                // Check row
                if (rows[i].find(num) != rows[i].end()) return false;
                rows[i].insert(num);

                // Check column
                if (cols[j].find(num) != cols[j].end()) return false;
                cols[j].insert(num);

                // Check 3x3 box
                int boxIndex = (i / 3) * 3 + (j / 3);
                if (boxes[boxIndex].find(num) != boxes[boxIndex].end()) return false;
                boxes[boxIndex].insert(num);
            }
        }

        return true;
    }
};

//--------------------------------------------------------------------------

//  Approach 2 : Using vectors

/* 
    Time complexity: O(1) for each cell, O(81) in total which simplifies to O(1)
    Space complexity: O(1) since the space used by the vectors is constant

   Explanation: 
   - We use three 2D vectors `rows`, `cols`, and one 3D vector `boxes` to keep track of the numbers seen in each row, column, and 3x3 sub-box respectively.
   - Each vector is initialized to store boolean values indicating whether a number (1-9) has been encountered.
   - As we iterate through each cell in the Sudoku board, we check if the current number has already been seen in the corresponding row, column, or 3x3 sub-box.
   - If it has been seen, we return false indicating the board is not valid.
   - If it hasn't been seen, we mark it as seen in the respective vectors.
   - This approach ensures that each number is checked in constant time O(1) and the overall complexity remains O(1) due to the fixed size of the board.
*/

class Solution2 {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> rows(9, vector<bool>(10, false));
        vector<vector<bool>> cols(9, vector<bool>(10, false));
        vector<vector<vector<bool>>> boxes(3, vector<vector<bool>>(3, vector<bool>(10, false)));

        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char num = board[i][j];
                if (num == '.') continue;

                int n = num - '0';


                // Check row
                if (rows[i][n]) return false;
                rows[i][n] = true;

                // Check column
                if (cols[j][n]) return false;
                cols[j][n] = true;

                // Check 3x3 box
                int boxRow = i / 3, boxCol = j / 3;
                if (boxes[boxRow][boxCol][n]) return false;
                boxes[boxRow][boxCol][n] = true;
            }
        }

        return true;
    }
};




void isValidSudoko (vector<vector<char>>& board) {
    Solution solution;
    if (solution.isValidSudoku(board)) cout << "The board is a valid Sudoku." << endl;
    else cout << "The board is not a valid Sudoku." << endl;
}

// Test
int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

        vector<vector<char>> board2 = {
        {'8', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };
    
    isValidSudoko(board);
    isValidSudoko(board2);

    return 0;
}

