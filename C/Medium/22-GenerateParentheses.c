// Description: https://leetcode.com/problems/generate-parentheses/description/

/*
    Approach: Recursive Backtracking

    Use backtracking to generate all valid combinations of parentheses.
    Maintain counters for open and close parentheses to ensure validity.
    Add '(' if open count < n, add ')' if close count < open count.
    When string reaches length 2*n, it's a valid combination.
    Use dynamic arrays to store results with proper memory management.

    Time complexity: O(4^n / sqrt(n)) - Catalan number growth.
    Space complexity: O(4^n / sqrt(n)) - Result storage + recursion stack.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables for backtracking
char** result;
int resultSize;
int resultCapacity;
char* current;
int currentSize;

// Helper function to add a result
void addResult() {
    if (resultSize >= resultCapacity) {
        resultCapacity = resultCapacity == 0 ? 8 : resultCapacity * 2;
        result = (char**)realloc(result, resultCapacity * sizeof(char*));
    }
    result[resultSize] = (char*)malloc((currentSize + 1) * sizeof(char));
    strcpy(result[resultSize], current);
    resultSize++;
}

// Recursive backtracking function
void backtrack(int n, int open, int close) {
    // Base case: reached target length
    if (currentSize == 2 * n) {
        addResult();
        return;
    }

    // Try adding '(' if we haven't used all opening brackets
    if (open < n) {
        current[currentSize++] = '(';
        backtrack(n, open + 1, close);
        currentSize--;  // backtrack
    }

    // Try adding ')' if it would balance or keep balance
    if (close < open) {
        current[currentSize++] = ')';
        backtrack(n, open, close + 1);
        currentSize--;  // backtrack
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis(int n, int* returnSize) {
    // Initialize global variables
    result = NULL;
    resultSize = 0;
    resultCapacity = 0;
    current = (char*)malloc((2 * n + 1) * sizeof(char));
    currentSize = 0;
    current[2 * n] = '\0';  // null terminate

    // Start backtracking
    backtrack(n, 0, 0);

    // Clean up
    free(current);

    // Set return size
    *returnSize = resultSize;
    return result;
}

// Test
void printResult(char** result, int size) {
    printf("Output: [");
    for (int i = 0; i < size; i++) {
        printf("\"%s\"", result[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]\n");
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main() {
    int returnSize;

    // Example 1: n = 3
    char** result1 = generateParenthesis(3, &returnSize);
    // Sort for consistent output
    qsort(result1, returnSize, sizeof(char*), compareStrings);
    printResult(result1, returnSize);

    // Free memory
    for (int i = 0; i < returnSize; i++) {
        free(result1[i]);
    }
    free(result1);

    // Example 2: n = 1
    char** result2 = generateParenthesis(1, &returnSize);
    printResult(result2, returnSize);

    // Free memory
    for (int i = 0; i < returnSize; i++) {
        free(result2[i]);
    }
    free(result2);

    return 0;
}
