// Description: https://leetcode.com/problems/container-with-most-water/description/

/*
    Approach: Two Pointers

    Start with pointers at both ends for maximum width container.
    Calculate area as min(height[left], height[right]) * (right - left).
    Move the pointer with smaller height inward to potentially find larger area.
    This greedy choice ensures we don't miss the optimal solution.
    Track the maximum area found during the iteration.
    Continue until both pointers meet.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer and area variables used.
*/

#include <stdio.h>

int max(int a, int b) { return (a > b) ? a : b; }
int min(int a, int b) { return (a < b) ? a : b; }

int maxArea(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int maxArea = 0;

    while (left < right) {
        int width = right - left;
        int currentHeight = min(height[left], height[right]);
        int currentArea = width * currentHeight;
        maxArea = max(maxArea, currentArea);

        if (height[left] < height[right])
            left++;
        else
            right--;
    }

    return maxArea;
}

// Test
int main() {
    // Example 1: height = [1,8,6,2,5,4,8,3,7]
    int height1[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    printf("Output: %d\n", maxArea(height1, 9));

    // Example 2: height = [1,1]
    int height2[] = {1, 1};
    printf("Output: %d\n", maxArea(height2, 2));

    return 0;
}