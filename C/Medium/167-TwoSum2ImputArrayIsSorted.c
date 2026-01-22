// Description: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

/*
    Approach: Two Pointers

    Use two pointers starting from both ends of the sorted array.
    Calculate sum of elements at both pointers.
    If sum equals target, return 1-indexed positions.
    If sum is too small, move left pointer right to increase sum.
    If sum is too large, move right pointer left to decrease sum.
    Sorted property guarantees exactly one solution exists.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));

    int left = 0;
    int right = numbersSize - 1;

    while (left < right) {
        int sum = numbers[left] + numbers[right];
        if (sum == target) {
            result[0] = left + 1;
            result[1] = right + 1;
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    return result;
}

// Test
int main() {
    int returnSize;

    // Example 1: numbers = [2,7,11,15], target = 9
    int numbers1[] = {2, 7, 11, 15};
    int* result1 = twoSum(numbers1, 4, 9, &returnSize);
    printf("Output: [%d, %d]\n", result1[0], result1[1]);
    free(result1);

    // Example 2: numbers = [2,3,4], target = 6
    int numbers2[] = {2, 3, 4};
    int* result2 = twoSum(numbers2, 3, 6, &returnSize);
    printf("Output: [%d, %d]\n", result2[0], result2[1]);
    free(result2);

    // Example 3: numbers = [-1,0], target = -1
    int numbers3[] = {-1, 0};
    int* result3 = twoSum(numbers3, 2, -1, &returnSize);
    printf("Output: [%d, %d]\n", result3[0], result3[1]);
    free(result3);

    return 0;
}
