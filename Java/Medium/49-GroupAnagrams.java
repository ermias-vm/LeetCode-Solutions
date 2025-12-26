// Description: https://leetcode.com/problems/group-anagrams/description/

/*
    Approach: Sorted String as Key

    Use a HashMap where the key is the sorted version of each string.
    Sorting a string's characters creates a canonical form for all its anagrams.
    All anagrams will have the same sorted form and group together.
    Iterate through input strings, sort each one, and add to corresponding group.
    Use putIfAbsent to initialize new groups and get() to add to existing ones.
    Finally, return all groups as an ArrayList of the map values.

    Time complexity: O(n * k log k) - n strings, each of max length k, sorted.
    Space complexity: O(n * k) - Storing all strings in HashMap.
*/

import java.util.*;
class Solution {

    public List<List<String>> groupAnagrams(String[] strs) {
        if (strs == null || strs.length == 0) {
            return new ArrayList<>();
        }

        Map<String, List<String>> map = new HashMap<>();

        for (String s : strs) {
            char[] arr = s.toCharArray();
            Arrays.sort(arr);
            String sortedKey = new String(arr);

            map.putIfAbsent(sortedKey, new ArrayList<>());
            map.get(sortedKey).add(s);
        }

        return new ArrayList<>(map.values());
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        String[] example1 = {"eat","tea","tan","ate","nat","bat"};
        String[] example2 = {""};
        String[] example3 = {"a"};

        List<List<String>> result1 = solution.groupAnagrams(example1);
        List<List<String>> result2 = solution.groupAnagrams(example2);
        List<List<String>> result3 = solution.groupAnagrams(example3);

        System.out.println("Example 1: " + result1);
        System.out.println("Example 2: " + result2);
        System.out.println("Example 3: " + result3);
    }
}
