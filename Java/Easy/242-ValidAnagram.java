import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

// Description: https://leetcode.com/problems/valid-anagram/description/

// Approach 1: Using frequency array (for lowercase English letters only)
/*
    Time complexity:    O(n)
    Space complexity:   O(1)
    
    The strategy used to solve the problem involves counting the frequency of each character in both strings.
    Two arrays of size 26 (for each letter in the alphabet) are used to store these frequencies.
    The characters in the strings are iterated over, and their corresponding counts are incremented.
    Finally, the two arrays are compared; if they are identical, the strings are anagrams.
*/
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

// Approach 2: Using HashMap (for any Unicode characters)
/*
    Time complexity:    O(n)
    Space complexity:   O(k) where 'k' is the number of distinct characters across both input
    
    This code replaces the fixed-size arrays with HashMap to count the frequency of each
    character in the input strings. This approach is more flexible and can handle any set of characters,
    making it suitable for Unicode characters as well.
*/
class Solution2 {
    public boolean isAnagram(String s, String t) {
        if (s.length() != t.length()) return false;
        
        Map<Character, Integer> countS = new HashMap<>();
        Map<Character, Integer> countT = new HashMap<>();
        
        for (int i = 0; i < s.length(); i++) {
            countS.put(s.charAt(i), countS.getOrDefault(s.charAt(i), 0) + 1);
            countT.put(t.charAt(i), countT.getOrDefault(t.charAt(i), 0) + 1);
        }
        
        return countS.equals(countT);
    }
}

// Test
class Test {
    public static void main(String[] args) {
        // Approach 1
        Solution solution = new Solution();
        System.out.println("=== Approach 1 (Array) ===");
        System.out.println("Input: s = \"anagram\", t = \"nagaram\"");
        System.out.println("Output: " + solution.isAnagram("anagram", "nagaram"));
        System.out.println();
        
        System.out.println("Input: s = \"rat\", t = \"car\"");
        System.out.println("Output: " + solution.isAnagram("rat", "car"));
        System.out.println();
        
        // Approach 2
        Solution2 solution2 = new Solution2();
        System.out.println("=== Approach 2 (HashMap - Unicode support) ===");
        System.out.println("Input: s = \"anagram\", t = \"nagaram\"");
        System.out.println("Output: " + solution2.isAnagram("anagram", "nagaram"));
        System.out.println();
        
        System.out.println("Input: s = \"rat\", t = \"car\"");
        System.out.println("Output: " + solution2.isAnagram("rat", "car"));
        System.out.println();
        
        // Unicode examples
        System.out.println("Unicode Input: s = \"🍎🍏\", t = \"🍏🍎\"");
        System.out.println("Output: " + solution2.isAnagram("🍎🍏", "🍏🍎"));
        System.out.println();
        
        System.out.println("Unicode Input: s = \"🍏🍏🍏\", t = \"🍎🍎🍎\"");
        System.out.println("Output: " + solution2.isAnagram("🍏🍏🍏", "🍎🍎🍎"));
    }
}
