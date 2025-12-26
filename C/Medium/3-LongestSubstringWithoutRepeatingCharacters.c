// Description: https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

/*
    Approach: Sliding Window

    Use an array of size 128 to track the last seen index of each ASCII character.
    Maintain a sliding window with start and end pointers.
    When a duplicate character is found, move start to the position after its last occurrence.
    Update the character's last seen index at each step.
    Track the maximum window length (end - start + 1) throughout the iteration.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(1) - Fixed size array of 128 characters.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);
    if (n == 0) return 0;
    
    int maxLength = 0;
    int charIndex[128];
    int start = 0;
    
    for (int i = 0; i < 128; i++) {
        charIndex[i] = -1;
    }
    
    for (int end = 0; end < n; end++) {
        if (charIndex[s[end]] >= start) {
            start = charIndex[s[end]] + 1;
        }
        
        charIndex[s[end]] = end;
        
        int currentLength = end - start + 1;
        if (currentLength > maxLength) {
            maxLength = currentLength;
        }
    }
    
    return maxLength;
}

// Test
int main() {

    // Test cases
    char test1[] = "abcabcbb";
    char test2[] = "bbbbb";
    char test3[] = "pwwkew";
    char test4[] = "";
    char test5[] = "dvdf";
    
    printf("Input: s = \"%s\"\n", test1);
    printf("Output: %d\n", lengthOfLongestSubstring(test1));
    printf("Expected: 3\n\n");
    
    printf("Input: s = \"%s\"\n", test2);
    printf("Output: %d\n", lengthOfLongestSubstring(test2));
    printf("Expected: 1\n\n");
    
    printf("Input: s = \"%s\"\n", test3);
    printf("Output: %d\n", lengthOfLongestSubstring(test3));
    printf("Expected: 3\n\n");
    
    printf("Input: s = \"%s\"\n", test4);
    printf("Output: %d\n", lengthOfLongestSubstring(test4));
    printf("Expected: 0\n\n");
    
    printf("Input: s = \"%s\"\n", test5);
    printf("Output: %d\n", lengthOfLongestSubstring(test5));
    printf("Expected: 3\n\n");
    
    return 0;
}
