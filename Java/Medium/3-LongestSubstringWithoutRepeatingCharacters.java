// Description:
// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

/*
    Approach: Sliding Window with Array

    Use an array of size 128 to track the last seen index of each ASCII character.
    Maintain a sliding window with start pointer and end pointer (loop variable).
    When a duplicate is found (last index >= start), move start past that index.
    Update the character's last seen index at each step.
    Track the maximum window length (end - start + 1) throughout iteration.
    The fixed-size array provides O(1) character index lookups.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(1) - Fixed size array of 128 elements.
*/

import java.util.*;

class Solution {
    public int lengthOfLongestSubstring(String s) {
        int n = s.length();
        int maxLength = 0;
        int[] charIndex = new int[128];
        Arrays.fill(charIndex, -1);
        int start = 0;

        for (int end = 0; end < n; end++) {
            char c = s.charAt(end);
            if (charIndex[c] >= start) {
                start = charIndex[c] + 1;
            }
            charIndex[c] = end;
            maxLength = Math.max(maxLength, end - start + 1);
        }

        return maxLength;
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: s = "abcabcbb"
        System.out.println("Output: " + solution.lengthOfLongestSubstring("abcabcbb"));

        // Example 2: s = "bbbbb"
        System.out.println("Output: " + solution.lengthOfLongestSubstring("bbbbb"));

        // Example 3: s = "pwwkew"
        System.out.println("Output: " + solution.lengthOfLongestSubstring("pwwkew"));
    }
}
