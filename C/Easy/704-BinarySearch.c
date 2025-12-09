#include <stdio.h>

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
    // Test case 1
    int nums1[] = {-1, 0, 3, 5, 9, 12};
    printf("Test case 1: %d\n", search(nums1, 6, 9));  // Output: 4

    // Test case 2
    int nums2[] = {-1, 0, 3, 5, 9, 12};
    printf("Test case 2: %d\n", search(nums2, 6, 2));  // Output: -1

    return 0;
}
