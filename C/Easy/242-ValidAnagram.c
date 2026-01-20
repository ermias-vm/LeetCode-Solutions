// Description: https://leetcode.com/problems/valid-anagram/description/

/*
    Approach: Character Count

    First check if strings have equal length; if not, they can't be anagrams.
    Use an array of size 26 to count character frequency differences.
    Increment count for characters in s, decrement for characters in t.
    If all counts are zero at the end, strings are anagrams.
    This approach works for lowercase English letters only.

    Time complexity: O(n) - Single pass through both strings.
    Space complexity: O(1) - Fixed size array of 26 elements.
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool isAnagram(char* s, char* t) {
    int lenS = strlen(s);
    int lenT = strlen(t);

    if (lenS != lenT) return false;

    int count[26] = {0};

    for (int i = 0; i < lenS; i++) {
        count[s[i] - 'a']++;
        count[t[i] - 'a']--;
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) return false;
    }

    return true;
}

// Test
int main() {
    // Example 1: s = "anagram", t = "nagaram"
    printf("Output: %s\n", isAnagram("anagram", "nagaram") ? "true" : "false");

    // Example 2: s = "rat", t = "car"
    printf("Output: %s\n", isAnagram("rat", "car") ? "true" : "false");

    return 0;
}
