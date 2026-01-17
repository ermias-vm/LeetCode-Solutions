// Description: https://leetcode.com/problems/trapping-rain-water/description/

/*
    Approach: Two Pointers

    Use two pointers starting from both ends of the height array.
    Maintain the maximum height seen from left and right sides.
    At each step, move the pointer with the smaller height inward.
    Water trapped at current position = max_height_from_side - current_height.
    Only count water if current height is less than the max from that side.
    Continue until both pointers meet.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer and max height variables used.
*/

#include <stdio.h>

int trap(int* height, int heightSize) {
    if (heightSize == 0) return 0;

    int left = 0;
    int right = heightSize - 1;
    int leftMax = 0;
    int rightMax = 0;
    int waterTrapped = 0;

    while (left < right) {
        if (height[left] < height[right]) {
            if (height[left] >= leftMax) leftMax = height[left];
            else waterTrapped += leftMax - height[left];
            left++;
        } else {
            if (height[right] >= rightMax) rightMax = height[right];
            else waterTrapped += rightMax - height[right];
            right--;
        }
    }

    return waterTrapped;
}

// Test
int main() {
    // Example 1: height = [0,1,0,2,1,0,1,3,2,1,2,1]
    int height1[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    printf("Output: %d\n", trap(height1, 12));

    // Example 2: height = [4,2,0,3,2,5]
    int height2[] = {4, 2, 0, 3, 2, 5};
    printf("Output: %d\n", trap(height2, 6));

    return 0;
}
