#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Description: https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

// Approach 1: Using array to track character indices )
int lengthOfLongestSubstring(char* s) {
    int n = strlen(s);
    if (n == 0) return 0;
    
    int maxLength = 0;
    int charIndex[128]; // Array to store last index of each ASCII character
    int start = 0;
    
    // Initialize all positions to -1
    for (int i = 0; i < 128; i++) {
        charIndex[i] = -1;
    }
    
    for (int end = 0; end < n; end++) {
        // If the current character was seen before and is within current window
        if (charIndex[s[end]] >= start) {
            start = charIndex[s[end]] + 1;
        }
        
        // Update the last seen index of current character
        charIndex[s[end]] = end;
        
        // Update maximum length if current window is larger
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
