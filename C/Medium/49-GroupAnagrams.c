#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Description: https://leetcode.com/problems/group-anagrams/description/

// Function for qsort to compare characters
int compareChar(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

// Function to sort a string
char* sortString(const char* s) {
    int len = strlen(s);
    char* sorted = malloc(len + 1);
    strcpy(sorted, s);
    qsort(sorted, len, sizeof(char), compareChar);
    return sorted;
}

// Function for qsort to compare pairs by sorted string
int comparePairs(const void* a, const void* b) {
    char* const* pairA = *(char* const**)a;
    char* const* pairB = *(char* const**)b;
    return strcmp(pairA[0], pairB[0]);
}

char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    if (strsSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    // Create pairs [sortedStr, originalStr]
    char*** pairs = malloc(strsSize * sizeof(char**));
    for (int i = 0; i < strsSize; i++) {
        pairs[i] = malloc(2 * sizeof(char*));
        pairs[i][0] = sortString(strs[i]);  // sorted
        pairs[i][1] = strs[i];              // original
    }

    // Sort pairs by sorted string
    qsort(pairs, strsSize, sizeof(char**), comparePairs);

    // Count groups
    int groupCount = 1;
    for (int i = 1; i < strsSize; i++) {
        if (strcmp(pairs[i][0], pairs[i-1][0]) != 0) groupCount++;
    }

    // Build result
    char*** result = malloc(groupCount * sizeof(char**));
    *returnColumnSizes = malloc(groupCount * sizeof(int));
    *returnSize = groupCount;

    int g = 0;
    (*returnColumnSizes)[g] = 1;
    result[g] = malloc(sizeof(char*));
    result[g][0] = pairs[0][1];

    for (int i = 1; i < strsSize; i++) {
        if (strcmp(pairs[i][0], pairs[i-1][0]) == 0) {
            // Same group - expand
            int oldSize = (*returnColumnSizes)[g];
            result[g] = realloc(result[g], (oldSize + 1) * sizeof(char*));
            result[g][oldSize] = pairs[i][1];
            (*returnColumnSizes)[g] = oldSize + 1;
        } else {
            // New group
            g++;
            (*returnColumnSizes)[g] = 1;
            result[g] = malloc(sizeof(char*));
            result[g][0] = pairs[i][1];
        }
    }

    // Cleanup
    for (int i = 0; i < strsSize; i++) {
        free(pairs[i][0]);
        free(pairs[i]);
    }
    free(pairs);

    return result;
}

// Test
int main() {
    char* strs[] = {"eat","tea","tan","ate","nat","bat"};
    int strsSize = 6;
    int returnSize;
    int* returnColumnSizes;

    char*** result = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);

    printf("Input: strs = [");
    for (int i = 0; i < strsSize; i++) {
        printf("\"%s\"", strs[i]);
        if (i < strsSize - 1) printf(",");
    }
    printf("]\n");

    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("\"%s\"", result[i][j]);
            if (j < returnColumnSizes[i] - 1) printf(",");
        }
        printf("]");
        if (i < returnSize - 1) printf(",");
        free(result[i]);
    }
    printf("]\n");

    free(result);
    free(returnColumnSizes);
    return 0;
}