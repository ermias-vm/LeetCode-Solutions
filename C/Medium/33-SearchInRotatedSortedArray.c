// Description: https://leetcode.com/problems/search-in-rotated-sorted-array/description/

/*
    Approach: Modified Binary Search

    Use binary search on a rotated sorted array.
    At each step, determine which half of the array is sorted.
    If nums[left] <= nums[mid], the left half is sorted.
    If nums[mid] <= nums[right], the right half is sorted.
    Check if target lies within the sorted half.
    If yes, search in that half; otherwise, search in the other half.
    Continue until target is found or search space is exhausted.

    Time complexity: O(log n) - Binary search halves search space each iteration.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] == target) return mid;

        // Left half is sorted
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        }
        // Right half is sorted
        else {
            if (nums[mid] < target && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
    }

    return -1;
}

// Test
int main() {
    // Example 1: nums = [4,5,6,7,0,1,2], target = 0
    int nums1[] = {4, 5, 6, 7, 0, 1, 2};
    printf("Output: %d\n", search(nums1, 7, 0));  // Expected: 4

    // Example 2: nums = [4,5,6,7,0,1,2], target = 3
    int nums2[] = {4, 5, 6, 7, 0, 1, 2};
    printf("Output: %d\n", search(nums2, 7, 3));  // Expected: -1

    // Example 3: nums = [1], target = 0
    int nums3[] = {1};
    printf("Output: %d\n", search(nums3, 1, 0));  // Expected: -1

    return 0;
}
