// Description: https://leetcode.com/problems/encode-and-decode-strings/description/

/*
    Approach: Length Prefix Encoding

    Encode: Prefix each string with its length followed by '#' delimiter.
    Also prefix the entire message with the list size and '#'.
    This handles any characters within strings including special characters.
    Decode: First extract list size, then iteratively extract each string.
    For each string, read the length before '#', then extract that many characters.
    This encoding is unambiguous and handles empty strings correctly.

    Time complexity: O(n) - Where n is total characters across all strings.
    Space complexity: O(n) - For the encoded/decoded strings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encode(char** strs, int strsSize) {
    // Calculate total length needed
    int totalLen = 20;  // For list size prefix
    for (int i = 0; i < strsSize; i++) {
        totalLen += strlen(strs[i]) + 12;  // Extra space for length prefix
    }

    char* encoded = malloc(totalLen);
    int pos = sprintf(encoded, "%d#", strsSize);

    for (int i = 0; i < strsSize; i++) {
        int len = strlen(strs[i]);
        pos += sprintf(encoded + pos, "%d#", len);
        memcpy(encoded + pos, strs[i], len);
        pos += len;
    }
    encoded[pos] = '\0';

    return encoded;
}

char** decode(char* s, int* returnSize) {
    // Extract list size
    int listSize = 0;
    int pos = 0;
    while (s[pos] != '#') {
        listSize = listSize * 10 + (s[pos] - '0');
        pos++;
    }
    pos++;  // Skip '#'

    *returnSize = listSize;
    char** decoded = malloc(listSize * sizeof(char*));

    for (int i = 0; i < listSize; i++) {
        // Extract word size
        int wordSize = 0;
        while (s[pos] != '#') {
            wordSize = wordSize * 10 + (s[pos] - '0');
            pos++;
        }
        pos++;  // Skip '#'

        // Extract word
        decoded[i] = malloc(wordSize + 1);
        memcpy(decoded[i], s + pos, wordSize);
        decoded[i][wordSize] = '\0';
        pos += wordSize;
    }

    return decoded;
}

// Test
void printDecoded(char** decoded, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("\"%s\"", decoded[i]);
        if (i < size - 1) printf(", ");
    }
    printf("]");
}

void runTest(char** strs, int strsSize) {
    printf("Input: [");
    for (int i = 0; i < strsSize; i++) {
        printf("\"%s\"", strs[i]);
        if (i < strsSize - 1) printf(", ");
    }
    printf("]\n");

    char* encoded = encode(strs, strsSize);
    int decodedSize;
    char** decoded = decode(encoded, &decodedSize);

    printf("Output: ");
    printDecoded(decoded, decodedSize);
    printf("\n\n");

    for (int i = 0; i < decodedSize; i++) free(decoded[i]);
    free(decoded);
    free(encoded);
}

int main() {
    // Example 1
    char* strs1[] = {"hello", "world"};
    runTest(strs1, 2);

    // Example 2
    char* strs2[] = {"", "a", "abc", "defg"};
    runTest(strs2, 4);

    return 0;
}
