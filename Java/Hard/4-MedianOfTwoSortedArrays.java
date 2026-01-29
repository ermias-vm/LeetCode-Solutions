// Description: https://leetcode.com/problems/median-of-two-sorted-arrays/description/

/*
    Approach: Binary Search on Smaller Array

    Binary search on the smaller array to find the correct partition point.
    The partition divides both arrays such that left elements <= right elements.
    Use Integer.MIN_VALUE and Integer.MAX_VALUE to handle edge cases at array boundaries.
    For valid partition: maxLeftX <= minRightY and maxLeftY <= minRightX.
    If total length is even, median = (max(lefts) + min(rights)) / 2.
    If odd, median = max(lefts). Adjust partition based on comparison.

    Time complexity: O(log(min(m, n))) - Binary search on smaller array.
    Space complexity: O(1) - Only pointer variables used.
*/

import java.util.*;

class Solution {
    public double findMedianSortedArrays(int[] nums1, int[] nums2) {
        if (nums1.length > nums2.length) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int x = nums1.length;
        int y = nums2.length;
        int low = 0, high = x;

        while (low <= high) {
            int partitionX = (low + high) / 2;
            int partitionY = (x + y + 1) / 2 - partitionX;

            int maxLeftX = (partitionX == 0) ? Integer.MIN_VALUE : nums1[partitionX - 1];
            int minRightX = (partitionX == x) ? Integer.MAX_VALUE : nums1[partitionX];

            int maxLeftY = (partitionY == 0) ? Integer.MIN_VALUE : nums2[partitionY - 1];
            int minRightY = (partitionY == y) ? Integer.MAX_VALUE : nums2[partitionY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((x + y) % 2 == 0) {
                    return (Math.max(maxLeftX, maxLeftY) + Math.min(minRightX, minRightY)) / 2.0;
                } else {
                    return Math.max(maxLeftX, maxLeftY);
                }
            } else if (maxLeftX > minRightY) {
                high = partitionX - 1;
            } else {
                low = partitionX + 1;
            }
        }

        throw new IllegalArgumentException("Input arrays are not sorted.");
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: nums1 = [1,3], nums2 = [2]
        int[] nums1a = {1, 3};
        int[] nums2a = {2};
        System.out.printf("Output: %.5f%n", solution.findMedianSortedArrays(nums1a, nums2a));

        // Example 2: nums1 = [1,2], nums2 = [3,4]
        int[] nums1b = {1, 2};
        int[] nums2b = {3, 4};
        System.out.printf("Output: %.5f%n", solution.findMedianSortedArrays(nums1b, nums2b));
    }
}
