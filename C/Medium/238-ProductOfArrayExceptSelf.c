// Description: https://leetcode.com/problems/product-of-array-except-self/description/

/*
    Approach: Prefix and Suffix Products

    For each position, the result is the product of all elements to the left
    multiplied by the product of all elements to the right.
    First pass: calculate prefix products and store in result array.
    Second pass: multiply each position by the suffix product (running product from right).
    This avoids using division and achieves O(1) extra space.

    Time complexity: O(n) - Two passes through the array.
    Space complexity: O(1) - Only the output array is used (not counting output).
*/

#include <stdio.h>
#include <stdlib.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int* result = (int*)malloc(numsSize * sizeof(int));

    // First pass: prefix products
    // result[i] = product of all elements to the left of i
    result[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        result[i] = result[i - 1] * nums[i - 1];
    }

    // Second pass: multiply by suffix products
    // suffix = product of all elements to the right of i
    int suffix = 1;
    for (int i = numsSize - 1; i >= 0; i--) {
        result[i] *= suffix;
        suffix *= nums[i];
    }

    return result;
}

// Helper to print array
void printArray(int* arr, int size) {
    printf("Output: [");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

// Test
int main() {
    // Example 1: nums = [1,2,3,4]
    // Expected: [24, 12, 8, 6]
    int nums1[] = {1, 2, 3, 4};
    int returnSize1;
    int* result1 = productExceptSelf(nums1, 4, &returnSize1);
    printArray(result1, returnSize1);
    free(result1);

    // Example 2: nums = [-1,1,0,-3,3]
    // Expected: [0, 0, 9, 0, 0]
    int nums2[] = {-1, 1, 0, -3, 3};
    int returnSize2;
    int* result2 = productExceptSelf(nums2, 5, &returnSize2);
    printArray(result2, returnSize2);
    free(result2);

    return 0;
}
