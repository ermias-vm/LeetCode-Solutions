// Description: https://leetcode.com/problems/<problem-name>/description/

/*
    Approach: <Approach Name>

    <Brief explanation of the algorithm>
    <Step 1>
    <Step 2>
    <...>

    Time complexity: O(?)
    Space complexity: O(?)
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Solution
// <return_type> <function_name>(<params>) {
//     
// }

// Helper to print array
void printArray(int* arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

// Test
int main() {
    // Example 1
    // Input: ...
    // Expected: ...
    printf("Output: ...\n");

    // Example 2
    // Input: ...
    // Expected: ...
    printf("Output: ...\n");

    return 0;
}
