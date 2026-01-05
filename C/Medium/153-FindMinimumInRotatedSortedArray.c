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

#include <stdio.h>

int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] > nums[right])
            left = mid + 1;
        else
            right = mid;
    }

    return nums[left];
}

// Test
int main() {
    // Example 1: nums = [3,4,5,1,2]
    int nums1[] = {3, 4, 5, 1, 2};
    printf("Output: %d\n", findMin(nums1, 5));

    // Example 2: nums = [4,5,6,7,0,1,2]
    int nums2[] = {4, 5, 6, 7, 0, 1, 2};
    printf("Output: %d\n", findMin(nums2, 7));

    // Example 3: nums = [11,13,15,17]
    int nums3[] = {11, 13, 15, 17};
    printf("Output: %d\n", findMin(nums3, 4));

    return 0;
}
