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

import java.util.Arrays;
class Solution {
    public int maxArea(int[] height) {
        int left = 0;
        int right = height.length - 1;
        int maxArea = 0;

        while (left < right) {
            int width = right - left;
            int currentHeight = Math.min(height[left], height[right]);
            int currentArea = width * currentHeight;
            maxArea = Math.max(maxArea, currentArea);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }

        return maxArea;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        int[] height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
        System.out.println("Input: height = " + Arrays.toString(height1));
        System.out.println("Output: " + solution.maxArea(height1));
        System.out.println();

        int[] height2 = {1, 1};
        System.out.println("Input: height = " + Arrays.toString(height2));
        System.out.println("Output: " + solution.maxArea(height2));
    }
}
