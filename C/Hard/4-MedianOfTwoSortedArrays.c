// Description: https://leetcode.com/problems/median-of-two-sorted-arrays/description/

/*
    Approach: Binary Search on Smaller Array

    Binary search on the smaller array to find the correct partition point.
    The partition divides both arrays such that left elements <= right elements.
    Use INT_MIN and INT_MAX to handle edge cases at array boundaries.
    For valid partition: maxLeftX <= minRightY and maxLeftY <= minRightX.
    If total length is even, median = (max(lefts) + min(rights)) / 2.
    If odd, median = max(lefts). Adjust partition based on comparison.

    Time complexity: O(log(min(m, n))) - Binary search on smaller array.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <stdio.h>
#include <limits.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}
int min(int a, int b) {
    return (a < b) ? a : b;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    // Ensure nums1 is the smaller array
    if (nums1Size > nums2Size) {
        return findMedianSortedArrays(nums2, nums2Size, nums1, nums1Size);
    }

    int x = nums1Size;
    int y = nums2Size;
    int low = 0, high = x;

    while (low <= high) {
        int partitionX = (low + high) / 2;
        int partitionY = (x + y + 1) / 2 - partitionX;

        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == x) ? INT_MAX : nums1[partitionX];

        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == y) ? INT_MAX : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((x + y) % 2 == 0) {
                return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            } else {
                return (double)max(maxLeftX, maxLeftY);
            }
        } else if (maxLeftX > minRightY) {
            high = partitionX - 1;
        } else {
            low = partitionX + 1;
        }
    }

    return 0.0;  // Should never reach here with valid input
}

// Test
int main() {
    // Example 1: nums1 = [1,3], nums2 = [2]
    int nums1a[] = {1, 3};
    int nums2a[] = {2};
    printf("Output: %.5f\n", findMedianSortedArrays(nums1a, 2, nums2a, 1));

    // Example 2: nums1 = [1,2], nums2 = [3,4]
    int nums1b[] = {1, 2};
    int nums2b[] = {3, 4};
    printf("Output: %.5f\n", findMedianSortedArrays(nums1b, 2, nums2b, 2));

    return 0;
}
