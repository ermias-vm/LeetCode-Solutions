// Description: https://leetcode.com/problems/largest-rectangle-in-histogram/description/

/*
    Approach: Monotonic Stack

    Maintain a monotonic increasing stack storing bar indices.
    For each bar, pop all taller bars from the stack.
    When popping, calculate the rectangle area using the popped bar as height.
    The width extends from current index to the index after the new stack top.
    Add a sentinel bar of height 0 at the end to flush remaining stack elements.
    Track the maximum area found during the process.

    Time complexity: O(n) - Each element is pushed and popped at most once.
    Space complexity: O(n) - Stack can contain at most n elements.
*/

#include <stdio.h>
#include <stdlib.h>

int largestRectangleArea(int* heights, int heightsSize) {
    int* stack = (int*)malloc((heightsSize + 1) * sizeof(int));
    int top = -1;
    int maxArea = 0;

    for (int i = 0; i <= heightsSize; i++) {
        int currHeight = (i == heightsSize) ? 0 : heights[i];

        while (top >= 0 && heights[stack[top]] > currHeight) {
            int height = heights[stack[top--]];
            int width = (top < 0) ? i : i - stack[top] - 1;
            int area = height * width;
            if (area > maxArea) maxArea = area;
        }
        stack[++top] = i;
    }

    free(stack);
    return maxArea;
}


// Test
int main() {
    // Test case 1
    int heights1[] = {2, 1, 5, 6, 2, 3};
    printf("Test case 1: %d\n", largestRectangleArea(heights1, 6)); // Output: 10

    // Test case 2
    int heights2[] = {2, 4};
    printf("Test case 2: %d\n", largestRectangleArea(heights2, 2)); // Output: 4

    return 0;
}
