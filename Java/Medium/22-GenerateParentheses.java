// Description: https://leetcode.com/problems/generate-parentheses/description/

/*
    Approach: Recursive Backtracking

    Use backtracking to generate all valid combinations of parentheses.
    Maintain counters for open and close parentheses to ensure validity.
    Add '(' if open count < n, add ')' if close count < open count.
    When string reaches length 2*n, it's a valid combination.

    Time complexity: O(4^n / sqrt(n)) - Catalan number growth.
    Space complexity: O(4^n / sqrt(n)) - Result storage + recursion stack.
*/

import java.util.*;

class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> result = new ArrayList<>();
        backtrack(result, new StringBuilder(), 0, 0, n);
        return result;
    }

    private void backtrack(List<String> result, StringBuilder current, int open, int close, int n) {
        // Base case: reached target length
        if (current.length() == 2 * n) {
            result.add(current.toString());
            return;
        }

        // Try adding '(' if we haven't used all opening brackets
        if (open < n) {
            current.append('(');
            backtrack(result, current, open + 1, close, n);
            current.deleteCharAt(current.length() - 1);
        }

        // Try adding ')' if it would balance or keep balance
        if (close < open) {
            current.append(')');
            backtrack(result, current, open, close + 1, n);
            current.deleteCharAt(current.length() - 1);
        }
    }
}

// Test
class Test {
    public static String formatResult(List<String> result) {
        Collections.sort(result);
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < result.size(); i++) {
            sb.append("\"").append(result.get(i)).append("\"");
            if (i < result.size() - 1) sb.append(", ");
        }
        sb.append("]");
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: n = 3
        // Expected: ["((()))", "(()())", "(())()", "()(())", "()()()"]
        System.out.println("Output: " + formatResult(solution.generateParenthesis(3)));

        // Example 2: n = 1
        // Expected: ["()"]
        System.out.println("Output: " + formatResult(solution.generateParenthesis(1)));
    }
}
