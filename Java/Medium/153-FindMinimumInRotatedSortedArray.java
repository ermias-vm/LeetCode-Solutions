// Description: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/

/*
    Approach: Binary Search

    Use binary search to find the minimum element in a rotated sorted array.
    Compare the middle element with the rightmost element.
    If nums[mid] > nums[right], the minimum is in the right half (excluding mid).
    Otherwise, the minimum is in the left half (including mid).
    Continue narrowing the search space until left equals right.
    The element at this position is the minimum.

    Time complexity: O(log n) - Binary search halves search space each iteration.
    Space complexity: O(1) - Only pointer variables used.
*/

import java.util.Arrays;
class Solution {
    public int findMin(int[] nums) {
        int left = 0;
        int right = nums.length - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) left = mid + 1;
            else right = mid;
        }

        return nums[left];
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        int[] nums1 = {3, 4, 5, 1, 2};
        System.out.println("Input: nums = " + Arrays.toString(nums1));
        System.out.println("Output: " + solution.findMin(nums1)); // 1
        System.out.println();

        int[] nums2 = {4, 5, 6, 7, 0, 1, 2};
        System.out.println("Input: nums = " + Arrays.toString(nums2));
        System.out.println("Output: " + solution.findMin(nums2)); // 0
        System.out.println();

        int[] nums3 = {11, 13, 15, 17};
        System.out.println("Input: nums = " + Arrays.toString(nums3));
        System.out.println("Output: " + solution.findMin(nums3)); // 11
    }
}
