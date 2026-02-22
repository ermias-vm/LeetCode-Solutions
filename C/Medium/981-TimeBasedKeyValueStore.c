// Description: https://leetcode.com/problems/time-based-key-value-store/description/

/*
    Approach: Hash Map with Binary Search

    Use a hash map with chaining to store keys.
    Each key maps to a dynamic array of (value, timestamp) pairs.
    Since timestamps are strictly increasing, the array is sorted.
    For set: append the (value, timestamp) pair to the key's array.
    For get: use binary search to find largest timestamp <= given timestamp.
    Return the corresponding value, or empty string if not found.

    Time complexity: O(1) for set, O(log n) for get (binary search).
    Space complexity: O(n) - Stores all key-value-timestamp entries.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10007
#define INITIAL_CAPACITY 100

typedef struct {
    char* value;
    int timestamp;
} Entry;

typedef struct KeyNode {
    char* key;
    Entry* entries;
    int size;
    int capacity;
    struct KeyNode* next;
} KeyNode;

typedef struct {
    KeyNode* buckets[HASH_SIZE];
} TimeMap;

unsigned int hash(const char* key) {
    unsigned int h = 0;
    while (*key) {
        h = h * 31 + *key++;
    }
    return h % HASH_SIZE;
}

TimeMap* timeMapCreate() {
    TimeMap* obj = (TimeMap*)malloc(sizeof(TimeMap));
    memset(obj->buckets, 0, sizeof(obj->buckets));
    return obj;
}

KeyNode* findOrCreateKey(TimeMap* obj, const char* key) {
    unsigned int h = hash(key);
    KeyNode* node = obj->buckets[h];

    while (node) {
        if (strcmp(node->key, key) == 0) return node;
        node = node->next;
    }

    // Create new node
    node = (KeyNode*)malloc(sizeof(KeyNode));
    node->key = strdup(key);
    node->capacity = INITIAL_CAPACITY;
    node->entries = (Entry*)malloc(node->capacity * sizeof(Entry));
    node->size = 0;
    node->next = obj->buckets[h];
    obj->buckets[h] = node;

    return node;
}

void timeMapSet(TimeMap* obj, char* key, char* value, int timestamp) {
    KeyNode* node = findOrCreateKey(obj, key);

    // Resize if needed
    if (node->size >= node->capacity) {
        node->capacity *= 2;
        node->entries = (Entry*)realloc(node->entries, node->capacity * sizeof(Entry));
    }

    node->entries[node->size].value = strdup(value);
    node->entries[node->size].timestamp = timestamp;
    node->size++;
}

char* timeMapGet(TimeMap* obj, char* key, int timestamp) {
    unsigned int h = hash(key);
    KeyNode* node = obj->buckets[h];

    while (node) {
        if (strcmp(node->key, key) == 0) break;
        node = node->next;
    }

    if (!node || node->size == 0) return "";

    // Binary search for largest timestamp <= given timestamp
    int left = 0, right = node->size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (node->entries[mid].timestamp <= timestamp) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (result == -1) return "";
    return node->entries[result].value;
}

void timeMapFree(TimeMap* obj) {
    for (int i = 0; i < HASH_SIZE; i++) {
        KeyNode* node = obj->buckets[i];
        while (node) {
            KeyNode* next = node->next;
            free(node->key);
            for (int j = 0; j < node->size; j++) {
                free(node->entries[j].value);
            }
            free(node->entries);
            free(node);
            node = next;
        }
    }
    free(obj);
}

// Test
int main() {
    TimeMap* timeMap = timeMapCreate();

    timeMapSet(timeMap, "foo", "bar", 1);
    printf("Output: %s\n", timeMapGet(timeMap, "foo", 1));  // "bar"
    printf("Output: %s\n", timeMapGet(timeMap, "foo", 3));  // "bar"

    timeMapSet(timeMap, "foo", "bar2", 4);
    printf("Output: %s\n", timeMapGet(timeMap, "foo", 4));  // "bar2"
    printf("Output: %s\n", timeMapGet(timeMap, "foo", 5));  // "bar2"

    timeMapFree(timeMap);

    return 0;
}
