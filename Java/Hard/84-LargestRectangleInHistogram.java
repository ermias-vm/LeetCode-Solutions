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

import java.util.*;

class Solution {
    public int largestRectangleArea(int[] heights) {
        Deque<Integer> stack = new ArrayDeque<>();
        int maxArea = 0;
        int n = heights.length;

        for (int i = 0; i <= n; i++) {
            int currHeight = (i == n) ? 0 : heights[i];

            while (!stack.isEmpty() && heights[stack.peek()] > currHeight) {
                int height = heights[stack.pop()];
                int width = stack.isEmpty() ? i : i - stack.peek() - 1;
                maxArea = Math.max(maxArea, height * width);
            }
            stack.push(i);
        }

        return maxArea;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: heights = [2,1,5,6,2,3]
        // Expected: 10
        int[] heights1 = {2, 1, 5, 6, 2, 3};
        System.out.println("Output: " + solution.largestRectangleArea(heights1));

        // Example 2: heights = [2,4]
        // Expected: 4
        int[] heights2 = {2, 4};
        System.out.println("Output: " + solution.largestRectangleArea(heights2));
    }
}
