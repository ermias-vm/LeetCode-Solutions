import java.util.Arrays;

// Description: https://leetcode.com/problems/binary-search/description/

/*
    Approach: Binary Search

    Time complexity: O(log n) - We divide the search space in half each iteration.
    Space complexity: O(1) - We use a constant amount of extra space.

    We use two pointers to define the search range.
    At each step, we compare the middle element with the target.
    If the middle element equals the target, we return its index.
    If the target is greater, we search the right half.
    If the target is smaller, we search the left half.
*/

// Solution
class Solution {
    public int search(int[] nums, int target) {
        int left = 0, right = nums.length - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        int[] nums1 = {-1, 0, 3, 5, 9, 12};
        int[] nums2 = {-1, 0, 3, 5, 9, 12};

        System.out.println("Test case 1: " + solution.search(nums1, 9));  // Output: 4
        System.out.println("Test case 2: " + solution.search(nums2, 2));  // Output: -1
    }
}
