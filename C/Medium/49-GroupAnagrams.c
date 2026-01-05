// Description: https://leetcode.com/problems/group-anagrams/description/

/*
    Approach: Sorted String as Key

    Create pairs of (sorted_string, original_string) for each input string.
    Sorting characters of a string creates a canonical form for all anagrams.
    Sort all pairs by their sorted string key.
    Group consecutive pairs with matching sorted keys together.
    Build the result by collecting strings from each group.
    This approach avoids hash tables by using sorting-based grouping.

    Time complexity: O(n * k log k) - n strings, each of max length k.
    Space complexity: O(n * k) - Storage for all string pairs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function for qsort to compare characters
int compareChar(const void* a, const void* b) { return (*(char*)a - *(char*)b); }

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
        if (strcmp(pairs[i][0], pairs[i - 1][0]) != 0) groupCount++;
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
        if (strcmp(pairs[i][0], pairs[i - 1][0]) == 0) {
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
int compareStrings(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

typedef struct {
    char** group;
    int size;
} Group;

int compareGroups(const void* a, const void* b) {
    Group* ga = (Group*)a;
    Group* gb = (Group*)b;
    // Sort by size first, then by first element alphabetically
    if (ga->size != gb->size) return ga->size - gb->size;
    return strcmp(ga->group[0], gb->group[0]);
}

void printResult(char*** result, int returnSize, int* returnColumnSizes) {
    // Sort elements within each group
    for (int i = 0; i < returnSize; i++) {
        qsort(result[i], returnColumnSizes[i], sizeof(char*), compareStrings);
    }
    
    // Sort groups by first element
    Group* groups = malloc(returnSize * sizeof(Group));
    for (int i = 0; i < returnSize; i++) {
        groups[i].group = result[i];
        groups[i].size = returnColumnSizes[i];
    }
    qsort(groups, returnSize, sizeof(Group), compareGroups);
    
    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < groups[i].size; j++) {
            printf("\"%s\"", groups[i].group[j]);
            if (j < groups[i].size - 1) printf(", ");
        }
        printf("]");
        if (i < returnSize - 1) printf(", ");
    }
    printf("]\n");
    
    free(groups);
}

int main() {
    int returnSize;
    int* returnColumnSizes;

    // Example 1: strs = ["eat","tea","tan","ate","nat","bat"]
    char* strs1[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    char*** result1 = groupAnagrams(strs1, 6, &returnSize, &returnColumnSizes);
    printResult(result1, returnSize, returnColumnSizes);
    for (int i = 0; i < returnSize; i++) free(result1[i]);
    free(result1);
    free(returnColumnSizes);

    // Example 2: strs = [""]
    char* strs2[] = {""};
    char*** result2 = groupAnagrams(strs2, 1, &returnSize, &returnColumnSizes);
    printResult(result2, returnSize, returnColumnSizes);
    for (int i = 0; i < returnSize; i++) free(result2[i]);
    free(result2);
    free(returnColumnSizes);

    // Example 3: strs = ["a"]
    char* strs3[] = {"a"};
    char*** result3 = groupAnagrams(strs3, 1, &returnSize, &returnColumnSizes);
    printResult(result3, returnSize, returnColumnSizes);
    for (int i = 0; i < returnSize; i++) free(result3[i]);
    free(result3);
    free(returnColumnSizes);

    return 0;
}
