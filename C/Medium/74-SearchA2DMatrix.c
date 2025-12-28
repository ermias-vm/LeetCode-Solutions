// Description: https://leetcode.com/problems/search-a-2d-matrix/description/

/*
    Approach: Binary Search

    Treat the 2D matrix as a flattened 1D sorted array.
    Use binary search on virtual indices from 0 to (m * n - 1).
    Convert 1D index to 2D coordinates: row = mid / n, col = mid % n.
    Compare the element at these coordinates with the target.
    Narrow search space based on comparison until target is found or exhausted.
    This approach leverages the matrix's sorted properties efficiently.

    Time complexity: O(log(m * n)) - Binary search on m * n elements.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <stdio.h>
#include <stdbool.h>

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    if (matrixSize == 0 || matrixColSize[0] == 0) return false;

    int m = matrixSize;
    int n = matrixColSize[0];
    int left = 0;
    int right = m * n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        int row = mid / n;
        int col = mid % n;
        int midVal = matrix[row][col];

        if (midVal == target)
            return true;
        else if (midVal < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return false;
}

// Test
int main() {
    // Test case 1
    int row1[] = {1, 3, 5, 7};
    int row2[] = {10, 11, 16, 20};
    int row3[] = {23, 30, 34, 60};
    int* matrix1[] = {row1, row2, row3};
    int colSize1[] = {4, 4, 4};
    int target1 = 3;

    printf("Test case 1: %s\n",
           searchMatrix(matrix1, 3, colSize1, target1) ? "true" : "false");  // Output: true

    // Test case 2
    int target2 = 13;
    printf("Test case 2: %s\n",
           searchMatrix(matrix1, 3, colSize1, target2) ? "true" : "false");  // Output: false

    return 0;
}
