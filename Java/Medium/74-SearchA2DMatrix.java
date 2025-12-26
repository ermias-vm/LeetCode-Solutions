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

import java.util.Arrays;
class Solution {
    public boolean searchMatrix(int[][] matrix, int target) {
        if (matrix.length == 0 || matrix[0].length == 0) return false;
        
        int m = matrix.length;
        int n = matrix[0].length;
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
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[][] matrix1 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target1 = 3;
        System.out.println("Input: matrix = " + Arrays.deepToString(matrix1) + ", target = " + target1);
        System.out.println("Output: " + solution.searchMatrix(matrix1, target1)); // true
        System.out.println();
        
        int[][] matrix2 = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
        int target2 = 13;
        System.out.println("Input: matrix = " + Arrays.deepToString(matrix2) + ", target = " + target2);
        System.out.println("Output: " + solution.searchMatrix(matrix2, target2)); // false
    }
}
