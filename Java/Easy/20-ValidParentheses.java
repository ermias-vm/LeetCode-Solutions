// Description: https://leetcode.com/problems/valid-parentheses/description/

/*
    Approach: Stack with HashMap

    Use a Stack to track opening brackets encountered during iteration.
    Store bracket pairs in a HashMap for O(1) matching lookups.
    For each opening bracket, push it onto the stack.
    For each closing bracket, check if stack is non-empty and top matches.
    If mismatch or stack empty on closing bracket, return false.
    After processing, stack should be empty for valid parentheses.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(n) - Stack stores at most n/2 opening brackets.
*/

import java.util.HashMap;
import java.util.Map;
import java.util.Stack;

// Solution
class Solution {
    public boolean isValid(String s) {
        Stack<Character> openedBrackets = new Stack<>();
        Map<Character, Character> bracketMap = new HashMap<>();
        bracketMap.put(')', '(');
        bracketMap.put(']', '[');
        bracketMap.put('}', '{');

        for (char c : s.toCharArray()) {
            if (bracketMap.containsKey(c)) { // closed bracket case
                if (openedBrackets.isEmpty() || openedBrackets.peek() != bracketMap.get(c))
                    return false;
                openedBrackets.pop();
            } else
                openedBrackets.push(c);
        }

        return openedBrackets.isEmpty();
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();
        String test1 = "()";
        String test2 = "()[]{}";
        String test3 = "(]";

        System.out.println("Input: " + test1);
        System.out.println("Output: " + solution.isValid(test1)); // Output: true

        System.out.println("Input: " + test2);
        System.out.println("Output: " + solution.isValid(test2)); // Output: true

        System.out.println("Input: " + test3);
        System.out.println("Output: " + solution.isValid(test3)); // Output: false
    }
}
