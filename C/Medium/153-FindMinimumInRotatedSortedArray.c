#include <stdio.h>

// Description: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/

/*
    Approach: Binary Search
    Compare mid element with the rightmost element.
    If nums[mid] > nums[right], the minimum is in the right half.
    Otherwise, the minimum is in the left half (including mid).
    
    Time complexity: O(log n) - Binary search.
    Space complexity: O(1) - We use a constant amount of extra space.
*/

int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) left = mid + 1;
        else right = mid;
    }
    
    return nums[left];
}


// Test
int main() {
    // Test case 1
    int nums1[] = {3, 4, 5, 1, 2};
    printf("Test case 1: %d\n", findMin(nums1, 5)); // Output: 1
    
    // Test case 2
    int nums2[] = {4, 5, 6, 7, 0, 1, 2};
    printf("Test case 2: %d\n", findMin(nums2, 7)); // Output: 0
    
    // Test case 3
    int nums3[] = {11, 13, 15, 17};
    printf("Test case 3: %d\n", findMin(nums3, 4)); // Output: 11

    return 0;
}
