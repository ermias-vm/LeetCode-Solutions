// Description: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

/*
    Approach: Two Pointers

    Use two pointers starting from both ends of the sorted array.
    Calculate sum of elements at both pointers.
    If sum equals target, return 1-indexed positions.
    If sum is too small, move left pointer right to increase sum.
    If sum is too large, move right pointer left to decrease sum.
    Sorted property guarantees exactly one solution exists.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer variables used.
*/

import java.util.Arrays;
class Solution {
    public int[] twoSum(int[] numbers, int target) {
        int left = 0, right = numbers.length - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return new int[]{left + 1, right + 1}; // 1-based indices
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        return new int[]{}; // Should never reach here given problem constraints
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        
        int[] numbers1 = {2, 7, 11, 15};
        int target1 = 9;
        int[] result1 = solution.twoSum(numbers1, target1);
        System.out.println("Input: numbers = " + Arrays.toString(numbers1) + ", target = " + target1);
        System.out.println("Output: " + Arrays.toString(result1));
        System.out.println();
        
        int[] numbers2 = {2, 3, 4};
        int target2 = 6;
        int[] result2 = solution.twoSum(numbers2, target2);
        System.out.println("Input: numbers = " + Arrays.toString(numbers2) + ", target = " + target2);
        System.out.println("Output: " + Arrays.toString(result2));
        System.out.println();
        
        int[] numbers3 = {-1, 0};
        int target3 = -1;
        int[] result3 = solution.twoSum(numbers3, target3);
        System.out.println("Input: numbers = " + Arrays.toString(numbers3) + ", target = " + target3);
        System.out.println("Output: " + Arrays.toString(result3));
    }
}