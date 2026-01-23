// Description: https://leetcode.com/problems/top-k-frequent-elements/description/

/*
    Approach: Hash Map + Bucket Sort

    Use a hash map to count the frequency of each element.
    Create buckets where index represents frequency count.
    Each bucket stores elements that appear that many times.
    Iterate from highest frequency bucket to collect top k elements.
    This avoids sorting and achieves O(n) time complexity.

    Time complexity: O(n) - Single pass for counting and bucket creation.
    Space complexity: O(n) - Hash map and buckets store at most n elements.
*/

#include <stdio.h>
#include <stdlib.h>

// Hash map entry for counting frequencies
typedef struct HashEntry {
    int key;
    int count;
    struct HashEntry* next;
} HashEntry;

#define HASH_SIZE 10007

unsigned int hash(int key) {
    unsigned int k = (unsigned int)(key < 0 ? -key : key);
    return k % HASH_SIZE;
}

HashEntry* findOrCreate(HashEntry** table, int key) {
    unsigned int h = hash(key);
    HashEntry* entry = table[h];

    while (entry) {
        if (entry->key == key) return entry;
        entry = entry->next;
    }

    // Create new entry
    entry = (HashEntry*)malloc(sizeof(HashEntry));
    entry->key = key;
    entry->count = 0;
    entry->next = table[h];
    table[h] = entry;
    return entry;
}

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    // Hash table for frequency counting
    HashEntry** hashTable = (HashEntry**)calloc(HASH_SIZE, sizeof(HashEntry*));

    // Count frequencies
    int uniqueCount = 0;
    for (int i = 0; i < numsSize; i++) {
        HashEntry* entry = findOrCreate(hashTable, nums[i]);
        if (entry->count == 0) uniqueCount++;
        entry->count++;
    }

    // Collect all unique entries
    HashEntry** entries = (HashEntry**)malloc(uniqueCount * sizeof(HashEntry*));
    int idx = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        HashEntry* entry = hashTable[i];
        while (entry) {
            entries[idx++] = entry;
            entry = entry->next;
        }
    }

    // Bucket sort by frequency
    // Buckets: index = frequency, value = list of elements with that frequency
    int** buckets = (int**)calloc(numsSize + 1, sizeof(int*));
    int* bucketSizes = (int*)calloc(numsSize + 1, sizeof(int));

    for (int i = 0; i < uniqueCount; i++) {
        int freq = entries[i]->count;
        if (!buckets[freq]) {
            buckets[freq] = (int*)malloc(uniqueCount * sizeof(int));
        }
        buckets[freq][bucketSizes[freq]++] = entries[i]->key;
    }

    // Collect top k elements from highest frequency buckets
    int* result = (int*)malloc(k * sizeof(int));
    *returnSize = 0;

    for (int freq = numsSize; freq >= 1 && *returnSize < k; freq--) {
        for (int i = 0; i < bucketSizes[freq] && *returnSize < k; i++) {
            result[(*returnSize)++] = buckets[freq][i];
        }
    }

    // Cleanup
    for (int i = 0; i < HASH_SIZE; i++) {
        HashEntry* entry = hashTable[i];
        while (entry) {
            HashEntry* next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(hashTable);
    free(entries);
    for (int i = 0; i <= numsSize; i++) {
        if (buckets[i]) free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);

    return result;
}

// Helper to print array
void printArray(int* arr, int size) {
    printf("Output: [");
    for (int i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(",");
    }
    printf("]\n");
}

// Test
int main() {
    // Example 1: nums = [1,1,1,2,2,3], k = 2
    // Expected: [1,2]
    int nums1[] = {1, 1, 1, 2, 2, 3};
    int returnSize1;
    int* result1 = topKFrequent(nums1, 6, 2, &returnSize1);
    printArray(result1, returnSize1);
    free(result1);

    // Example 2: nums = [1], k = 1
    // Expected: [1]
    int nums2[] = {1};
    int returnSize2;
    int* result2 = topKFrequent(nums2, 1, 1, &returnSize2);
    printArray(result2, returnSize2);
    free(result2);

    // Example 3: nums = [1,2,1,2,1,2,3,1,3,2], k = 2
    // Expected: [1,2]
    int nums3[] = {1, 2, 1, 2, 1, 2, 3, 1, 3, 2};
    int returnSize3;
    int* result3 = topKFrequent(nums3, 10, 2, &returnSize3);
    printArray(result3, returnSize3);
    free(result3);

    return 0;
}
