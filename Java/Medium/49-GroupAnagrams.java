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
    public static String formatResult(List<List<String>> result) {
        // Sort elements within each group
        for (List<String> group : result) {
            Collections.sort(group);
        }
        // Sort groups by size first, then by first element
        result.sort((a, b) -> {
            if (a.size() != b.size()) return a.size() - b.size();
            return a.get(0).compareTo(b.get(0));
        });

        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < result.size(); i++) {
            sb.append("[");
            for (int j = 0; j < result.get(i).size(); j++) {
                sb.append("\"").append(result.get(i).get(j)).append("\"");
                if (j < result.get(i).size() - 1) sb.append(", ");
            }
            sb.append("]");
            if (i < result.size() - 1) sb.append(", ");
        }
        sb.append("]");
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: strs = ["eat","tea","tan","ate","nat","bat"]
        String[] example1 = {"eat", "tea", "tan", "ate", "nat", "bat"};
        List<List<String>> result1 = solution.groupAnagrams(example1);
        System.out.println("Output: " + formatResult(result1));

        // Example 2: strs = [""]
        String[] example2 = {""};
        List<List<String>> result2 = solution.groupAnagrams(example2);
        System.out.println("Output: " + formatResult(result2));

        // Example 3: strs = ["a"]
        String[] example3 = {"a"};
        List<List<String>> result3 = solution.groupAnagrams(example3);
        System.out.println("Output: " + formatResult(result3));
    }
}
