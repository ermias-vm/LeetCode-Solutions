// Description: https://leetcode.com/problems/valid-anagram/description/

/*
    Approach: Frequency Array

    First check if strings have equal length; if not, they can't be anagrams.
    Use two integer arrays of size 26 to count character frequencies.
    Iterate through both strings simultaneously, incrementing respective counts.
    Use character arithmetic (char - 'a') to map characters to array indices.
    Compare the frequency arrays using Arrays.equals() at the end.
    If identical, strings are anagrams; otherwise, they are not.

    Time complexity: O(n) - Single pass through both strings.
    Space complexity: O(1) - Fixed size arrays of 26 elements.
*/

import java.util.Arrays;

// Solution
class Solution {
    public boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) return false;

        int[] countS = new int[26];
        int[] countT = new int[26];

        for (int i = 0; i < s.length(); i++) {
            countS[s.charAt(i) - 'a']++;
            countT[t.charAt(i) - 'a']++;
        }

        return Arrays.equals(countS, countT);
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        System.out.println("Input: s = \"anagram\", t = \"nagaram\"");
        System.out.println("Output: " + solution.isAnagram("anagram", "nagaram"));
        System.out.println();

        System.out.println("Input: s = \"rat\", t = \"car\"");
        System.out.println("Output: " + solution.isAnagram("rat", "car"));
    }
}
