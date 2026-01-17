// Description: https://leetcode.com/problems/search-a-2d-matrix/description/

/*
    Approach: Binary Search

    Treat the 2D matrix as a flattened 1D sorted array.
    Use binary search on virtual indices from 0 to (m * n - 1).
    Convert 1D index to 2D coordinates: row = mid / n, col = mid % n.
    Compare the element at these coordinates with the target.
    Narrow search space based on comparison until target is found or exhausted.
    This approach leverages the matrix's row-major sorted properties.

    Time complexity: O(log(m * n)) - Binary search on m * n elements.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;

        int m = matrix.size();
        int n = matrix[0].size();
        int left = 0;
        int right = m * n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            int row = mid / n;
            int col = mid % n;
            int midVal = matrix[row][col];

            if (midVal == target) return true;
            else if (midVal < target) left = mid + 1;
            else right = mid - 1;
        }

        return false;
    }
};

// Test
int main() {
    Solution solution;

    // Example 1: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,50]], target = 3
    vector<vector<int>> matrix1 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
    cout << "Output: " << (solution.searchMatrix(matrix1, 3) ? "true" : "false") << endl;

    // Example 2: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
    vector<vector<int>> matrix2 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    cout << "Output: " << (solution.searchMatrix(matrix2, 13) ? "true" : "false") << endl;

    return 0;
}
