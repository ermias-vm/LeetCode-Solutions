// Description: https://leetcode.com/problems/contains-duplicate/description/

/*
    Approach: Sorting

    Sort the array in ascending order using qsort.
    After sorting, duplicate elements will be adjacent to each other.
    Iterate through the sorted array comparing each element with the previous one.
    If any two adjacent elements are equal, a duplicate exists.
    This approach trades time for space compared to hash-based solutions.

    Time complexity: O(n log n) - Due to sorting.
    Space complexity: O(1) - Sorting is done in-place.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

bool containsDuplicate(int* nums, int numsSize) {
    if (numsSize <= 1) return false;

    qsort(nums, numsSize, sizeof(int), compare);

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) { return true; }
    }

    return false;
}

// Test
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(",");
    }
    printf("]");
}

int main(void) {
    int nums1[] = {1, 2, 3, 1};
    int nums1Size = sizeof(nums1) / sizeof(nums1[0]);
    printf("Input: nums = ");
    printArray(nums1, nums1Size);
    printf("\nOutput: %s\n", containsDuplicate(nums1, nums1Size) ? "true" : "false");

    int nums2[] = {1, 2, 3, 4};
    int nums2Size = sizeof(nums2) / sizeof(nums2[0]);
    printf("\nInput: nums = ");
    printArray(nums2, nums2Size);
    printf("\nOutput: %s\n", containsDuplicate(nums2, nums2Size) ? "true" : "false");

    int nums3[] = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    int nums3Size = sizeof(nums3) / sizeof(nums3[0]);
    printf("\nInput: nums = ");
    printArray(nums3, nums3Size);
    printf("\nOutput: %s\n", containsDuplicate(nums3, nums3Size) ? "true" : "false");

    return 0;
}
