// Description: https://leetcode.com/problems/valid-palindrome/description/

/*
    Approach: Two Pointers

    Use two pointers starting from both ends of the string.
    Skip non-alphanumeric characters using Character.isLetterOrDigit().
    Compare characters in lowercase using Character.toLowerCase().
    If any mismatch is found, return false immediately.
    Move pointers toward center until they meet.
    Return true if all comparisons passed.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(1) - Only two pointer variables used.
*/

import java.util.Locale;

// Solution
class Solution {
    public boolean isPalindrome(String s) {
        int left = 0, right = s.length() - 1;
        while (left < right) {
            while (left < right && !Character.isLetterOrDigit(s.charAt(left))) left++;
            while (left < right && !Character.isLetterOrDigit(s.charAt(right))) right--;

            if (Character.toLowerCase(s.charAt(left)) != Character.toLowerCase(s.charAt(right))) return false;
    
            left++;
            right--;
        }
        return true;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        String s1 = "A man, a plan, a canal: Panama";
        String s2 = "race a car";
        String s3 = " ";

        System.out.println("Input: " + s1);
        System.out.println("Output: " + solution.isPalindrome(s1)); // true
        
        System.out.println("Input: " + s2);
        System.out.println("Output: " + solution.isPalindrome(s2)); // false
        
        System.out.println("Input: " + s3);
        System.out.println("Output: " + solution.isPalindrome(s3)); // true
    }
}
