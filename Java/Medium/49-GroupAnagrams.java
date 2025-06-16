import java.util.*;

// Description:  https://leetcode.com/problems/group-anagrams/description/

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
