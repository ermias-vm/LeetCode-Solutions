import java.util.Stack;
import java.util.HashMap;
import java.util.Map;

// Description: https://leetcode.com/problems/valid-parentheses/

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
                if (openedBrackets.isEmpty() || openedBrackets.peek() != bracketMap.get(c)) return false;
                openedBrackets.pop();
            }
            else openedBrackets.push(c);
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
