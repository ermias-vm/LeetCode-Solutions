// Description: https://leetcode.com/problems/daily-temperatures/description/

/*
    Approach: Monotonic Stack

    Use a monotonic decreasing stack that stores indices of temperatures.
    For each new temperature, pop indices from the stack while current temp is warmer.
    For each popped index, calculate the wait time as (current_index - popped_index).
    Push the current index onto the stack after processing.
    Elements remaining in the stack have no warmer day (answer stays 0).
    Each element is pushed and popped at most once.

    Time complexity: O(n) - Single pass with constant time operations per element.
    Space complexity: O(n) - Stack can contain at most n indices.
*/

#include <stdio.h>
#include <stdlib.h>

int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* answer = (int*)malloc(temperaturesSize * sizeof(int));
    int* stack = (int*)malloc(temperaturesSize * sizeof(int));  // Stack of indices
    int top = -1;

    for (int i = 0; i < temperaturesSize; i++) {
        answer[i] = 0;
    }

    for (int i = 0; i < temperaturesSize; i++) {
        while (top >= 0 && temperatures[stack[top]] < temperatures[i]) {
            int prevIndex = stack[top--];
            answer[prevIndex] = i - prevIndex;
        }
        stack[++top] = i;
    }

    free(stack);
    return answer;
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
    int returnSize;

    // Test case 1
    int temps1[] = {73, 74, 75, 71, 69, 72, 76, 73};
    int* result1 = dailyTemperatures(temps1, 8, &returnSize);
    printf("Test 1: ");
    printArray(result1, returnSize);
    printf("\n");  // Expected: [1, 1, 4, 2, 1, 1, 0, 0]
    free(result1);

    // Test case 2
    int temps2[] = {30, 40, 50, 60};
    int* result2 = dailyTemperatures(temps2, 4, &returnSize);
    printf("Test 2: ");
    printArray(result2, returnSize);
    printf("\n");  // Expected: [1, 1, 1, 0]
    free(result2);

    // Test case 3
    int temps3[] = {30, 60, 90};
    int* result3 = dailyTemperatures(temps3, 3, &returnSize);
    printf("Test 3: ");
    printArray(result3, returnSize);
    printf("\n");  // Expected: [1, 1, 0]
    free(result3);

    return 0;
}
