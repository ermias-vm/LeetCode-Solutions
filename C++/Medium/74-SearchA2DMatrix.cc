#include <iostream>
#include <vector>

using namespace std;

// Description: https://leetcode.com/problems/search-a-2d-matrix/description/

// Approach: Binary Search
// Treat the 2D matrix as a flattened 1D sorted array.
// Use binary search on indices 0 to (m * n - 1).
// Convert 1D index to 2D: row = mid / n, col = mid % n.

/* 
    Time complexity: O(log(m * n)) - Binary search on m * n elements.
    Space complexity: O(1) - We use a constant amount of extra space.
*/


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
    
    vector<vector<int>> matrix1 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target1 = 3;
    cout << "Test case 1: " << (solution.searchMatrix(matrix1, target1) ? "true" : "false") << endl; // Output: true
    
    vector<vector<int>> matrix2 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target2 = 13;
    cout << "Test case 2: " << (solution.searchMatrix(matrix2, target2) ? "true" : "false") << endl; // Output: false

    return 0;
}
