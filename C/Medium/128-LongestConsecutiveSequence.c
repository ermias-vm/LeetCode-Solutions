#include <stdio.h>
#include <stdlib.h>

// Description: https://leetcode.com/problems/longest-consecutive-sequence/description/

/*
    Approach: Sort and count consecutive elements
    
    Time complexity: O(n log n) due to sorting
    Space complexity: O(1)
*/

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    qsort(nums, numsSize, sizeof(int), compare);

    int longestStreak = 1;
    int currentStreak = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] == nums[i - 1]) continue;  
        else if (nums[i] == nums[i - 1] + 1) currentStreak++;
        else {
            if (currentStreak > longestStreak) longestStreak = currentStreak;
            currentStreak = 1;
        }
    }

    if (currentStreak > longestStreak) longestStreak = currentStreak;
    return longestStreak;
}


// Test
void printArray(int* nums, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", nums[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

int main() {
    // Test case 1
    int nums1[] = {100, 4, 200, 1, 3, 2};
    int size1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Input: nums = ");
    printArray(nums1, size1);
    printf("\nOutput: %d\n\n", longestConsecutive(nums1, size1));
    
    // Test case 2  
    int nums2[] = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    int size2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Input: nums = ");
    printArray(nums2, size2);
    printf("\nOutput: %d\n\n", longestConsecutive(nums2, size2));
    
    // Test case 3
    int nums3[] = {1, 0, 1, 2};
    int size3 = sizeof(nums3) / sizeof(nums3[0]);
    printf("Input: nums = ");
    printArray(nums3, size3);
    printf("\nOutput: %d\n", longestConsecutive(nums3, size3));
    
    return 0;
}