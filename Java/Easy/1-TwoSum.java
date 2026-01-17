// Description: https://leetcode.com/problems/two-sum/description/

/*
    Approach: Hash Map

    Use a HashMap to store each number and its index as we iterate.
    For each element, calculate its complement (target - current number).
    Check if the complement already exists in the HashMap.
    If found, return the complement's index and current index.
    Otherwise, store the current number and index in the map.
    This achieves single-pass lookup with O(1) average time per operation.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(n) - HashMap stores at most n elements.
*/

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

// Solution
class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> numMap = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (numMap.containsKey(complement)) {
                return new int[] {numMap.get(complement), i};
            }
            numMap.put(nums[i], i);
        }
        return new int[] {};
    }
}

// Test
class Test {
    public static void runTest(int[] nums, int target) {
        Solution solution = new Solution();
        int[] result = solution.twoSum(nums, target);
        System.out.println("Input: nums = " + Arrays.toString(nums) + ", target = " + target);
        System.out.println("Output: " + Arrays.toString(result));
        System.out.println();
    }

    public static void main(String[] args) {
        // Example 1
        runTest(new int[] {2, 7, 11, 15}, 9);

        // Example 2
        runTest(new int[] {3, 2, 4}, 6);

        // Example 3
        runTest(new int[] {3, 3}, 6);
    }
}
