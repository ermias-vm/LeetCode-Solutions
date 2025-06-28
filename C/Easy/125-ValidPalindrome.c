#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Description: https://leetcode.com/problems/valid-palindrome/description/

/*
    Approach: Two Pointers
    
    Time complexity: O(n)
    Space complexity: O(1)
*/

bool isPalindrome(char* s) {
    int len = strlen(s);
    int left = 0, right = len - 1;
    
    while (left < right) {
        // Skip non-alphanumeric characters from left
        while (left < right && !isalnum(s[left])) left++;
        
        // Skip non-alphanumeric characters from right
        while (left < right && !isalnum(s[right])) right--;
        
        // Compare characters (case-insensitive)
        if (tolower(s[left]) != tolower(s[right])) return false;
        
        left++;
        right--;
    }
    
    return true;
}

// Test
int main() {
    char* s1 = "A man, a plan, a canal: Panama";
    char* s2 = "race a car";
    char* s3 = " ";
    
    printf("Input: s = \"%s\"\n", s1);
    printf("Output: %s\n\n", isPalindrome(s1) ? "true" : "false");
    
    printf("Input: s = \"%s\"\n", s2);
    printf("Output: %s\n\n", isPalindrome(s2) ? "true" : "false");
    
    printf("Input: s = \"%s\"\n", s3);
    printf("Output: %s\n", isPalindrome(s3) ? "true" : "false");
    
    return 0;
}