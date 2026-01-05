// Description: https://leetcode.com/problems/binary-search/description/

/*
    Approach: Binary Search

    Use two pointers (left and right) to define the search range.
    Calculate the middle index to avoid integer overflow: mid = left + (right - left) / 2.
    Compare the middle element with the target value.
    If equal, return the index. If target is greater, search the right half.
    If target is smaller, search the left half.
    Repeat until the target is found or the search space is exhausted.

    Time complexity: O(log n) - Search space halves each iteration.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <stdio.h>

int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;

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

// Test
int main() {
    // Example 1: nums = [-1,0,3,5,9,12], target = 9
    int nums1[] = {-1, 0, 3, 5, 9, 12};
    printf("Output: %d\n", search(nums1, 6, 9));

    // Example 2: nums = [-1,0,3,5,9,12], target = 2
    int nums2[] = {-1, 0, 3, 5, 9, 12};
    printf("Output: %d\n", search(nums2, 6, 2));

    return 0;
}
