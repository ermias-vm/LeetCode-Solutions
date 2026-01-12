// Description: https://leetcode.com/problems/3sum/description/

/*
    Approach: Sorting + Two Pointers

    Sort the array to enable two-pointer technique and duplicate handling.
    Fix one element and use two pointers to find pairs summing to its negation.
    Skip duplicate values for the fixed element to avoid repeated triplets.
    For valid triplets, also skip duplicates for the other two elements.
    Move pointers based on current sum: left++ if too small, right-- if too large.
    Continue until all elements have been considered as the fixed element.

    Time complexity: O(n^2) - O(n log n) sort + O(n^2) two-pointer search.
    Space complexity: O(1) - Excluding the output array.
*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    // Start with NULL result, will allocate as needed
    int** result = NULL;
    *returnColumnSizes = NULL;
    *returnSize = 0;
    int capacity = 0;

    for (int i = 0; i < numsSize; i++) {
        // Skip duplicates for the fixed element
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0) {
                // Found a triplet - expand arrays if needed
                if (*returnSize >= capacity) {
                    capacity = capacity == 0 ? 8 : capacity * 2;
                    result = (int**)realloc(result, capacity * sizeof(int*));
                    *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                }

                result[*returnSize] = (int*)malloc(3 * sizeof(int));
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // Skip duplicates for left pointer
                while (left < right && nums[left] == nums[left + 1]) left++;
                // Skip duplicates for right pointer
                while (left < right && nums[right] == nums[right - 1]) right--;

                left++;
                right--;
            } else if (sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }

    return result;
}

// Test
void printResult(int** result, int returnSize, int* returnColumnSizes) {
    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d", result[i][j]);
            if (j < returnColumnSizes[i] - 1) printf(", ");
        }
        printf("]");
        if (i < returnSize - 1) printf(", ");
    }
    printf("]\n");
}

int main() {
    int returnSize;
    int* returnColumnSizes;

    // Example 1: nums = [-1,0,1,2,-1,-4]
    int nums1[] = {-1, 0, 1, 2, -1, -4};
    int** result1 = threeSum(nums1, 6, &returnSize, &returnColumnSizes);
    printResult(result1, returnSize, returnColumnSizes);

    // Free memory for example 1
    for (int i = 0; i < returnSize; i++) {
        free(result1[i]);
    }
    free(result1);
    free(returnColumnSizes);

    // Example 2: nums = [0,1,1]
    int nums2[] = {0, 1, 1};
    result1 = threeSum(nums2, 3, &returnSize, &returnColumnSizes);
    printResult(result1, returnSize, returnColumnSizes);

    // Free memory for example 2
    for (int i = 0; i < returnSize; i++) {
        free(result1[i]);
    }
    free(result1);
    free(returnColumnSizes);

    // Example 3: nums = [0,0,0]
    int nums3[] = {0, 0, 0};
    result1 = threeSum(nums3, 3, &returnSize, &returnColumnSizes);
    printResult(result1, returnSize, returnColumnSizes);

    // Free memory for example 3
    for (int i = 0; i < returnSize; i++) {
        free(result1[i]);
    }
    free(result1);
    free(returnColumnSizes);

    return 0;
}