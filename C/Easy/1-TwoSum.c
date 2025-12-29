// Description: https://leetcode.com/problems/two-sum/description/

/*
    Approach: Sorting + Two Pointers

    Create pairs of (value, original_index) to preserve original positions after sorting.
    Sort pairs by value in ascending order.
    Use two pointers starting from both ends of the sorted array.
    Move left pointer right if sum is too small, right pointer left if too large.
    When sum equals target, return the original indices of both elements.

    Time complexity: O(n log n) - Due to sorting.
    Space complexity: O(n) - For the pair array.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Pair;

int compare(const void* a, const void* b) {
    Pair* pairA = (Pair*)a;
    Pair* pairB = (Pair*)b;
    return pairA->value - pairB->value;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;

    Pair* pairs = (Pair*)malloc(numsSize * sizeof(Pair));
    for (int i = 0; i < numsSize; i++) {
        pairs[i].value = nums[i];
        pairs[i].index = i;
    }

    qsort(pairs, numsSize, sizeof(Pair), compare);

    int left = 0, right = numsSize - 1;
    while (left < right) {
        int sum = pairs[left].value + pairs[right].value;
        if (sum == target) {
            int* result = (int*)malloc(2 * sizeof(int));
            result[0] = pairs[left].index;
            result[1] = pairs[right].index;

            if (result[0] > result[1]) {
                int temp = result[0];
                result[0] = result[1];
                result[1] = temp;
            }

            free(pairs);
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    free(pairs);
    return NULL;
}

// Test
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

void runTest(int* nums, int numsSize, int target) {
    int returnSize;

    printf("Input: nums = ");
    printArray(nums, numsSize);
    printf(", target = %d\n", target);

    int* result = twoSum(nums, numsSize, target, &returnSize);

    if (result != NULL) {
        printf("Output: ");
        printArray(result, returnSize);
        printf("\n\n");
        free(result);
    }
}

int main() {
    // Example 1
    int nums1[] = {2, 7, 11, 15};
    runTest(nums1, 4, 9);

    // Example 2
    int nums2[] = {3, 2, 4};
    runTest(nums2, 3, 6);

    // Example 3
    int nums3[] = {3, 3};
    runTest(nums3, 2, 6);

    return 0;
}
