#include <stdio.h>
#include <stdlib.h>

// Description: https://leetcode.com/problems/two-sum/description/

/*
    Approach: Hash table simulation using sorted array approach
    
    Time complexity: O(n log n) due to sorting
    Space complexity: O(n) for the pair array
    
    Explanation:
    - Create pairs of (value, original_index) to track original positions after sorting
    - Sort pairs by value using qsort
    - Use two pointers technique to find the target sum
    - Return the original indices from the pairs
*/


typedef struct {
    int value;
    int index;
} Pair;

// Comparator function for qsort
int compare(const void* a, const void* b) {
    Pair* pairA = (Pair*)a;
    Pair* pairB = (Pair*)b;
    return pairA->value - pairB->value;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    
    // Create array of pairs (value, original_index)
    Pair* pairs = (Pair*)malloc(numsSize * sizeof(Pair));
    for (int i = 0; i < numsSize; i++) {
        pairs[i].value = nums[i];
        pairs[i].index = i;
    }
    
    // Sort pairs by value
    qsort(pairs, numsSize, sizeof(Pair), compare);
    
    // Use two pointers to find target sum
    int left = 0, right = numsSize - 1;
    while (left < right) {
        int sum = pairs[left].value + pairs[right].value;
        if (sum == target) {
            // Found the solution - return original indices
            int* result = (int*)malloc(2 * sizeof(int));
            result[0] = pairs[left].index;
            result[1] = pairs[right].index;
            
            // Ensure result[0] < result[1]
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

int main() {
    int nums[] = {2, 7, 11, 15};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int target = 9;
    int returnSize;
    
    printf("Input: nums = ");
    printArray(nums, numsSize);
    printf(", target = %d\n", target);
    
    int* result = twoSum(nums, numsSize, target, &returnSize);
    
    if (result != NULL) {
        printf("Output: ");
        printArray(result, returnSize);
        printf("\n");
        free(result);
    } else {
        printf("No two sum solution found.\n");
    }
    
    return 0;
}