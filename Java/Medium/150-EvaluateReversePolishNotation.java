// Description: https://leetcode.com/problems/evaluate-reverse-polish-notation/description/

/*
    Approach: Stack

    Use a stack to evaluate the Reverse Polish Notation expression.
    Push operands (numbers) onto the stack as encountered.
    For operators, pop two operands from the stack (second popped is left operand).
    Apply the operation and push the result back onto the stack.
    Integer division truncates toward zero as required.
    Final result is the only element remaining on the stack.

    Time complexity: O(n) - Single pass through the tokens.
    Space complexity: O(n) - Stack stores at most n/2 operands.
*/

import java.util.*;

class Solution {
    public int evalRPN(String[] tokens) {
        Deque<Integer> stack = new ArrayDeque<>();

        for (String token : tokens) {
            if (token.length() == 1 && "+-*/".contains(token)) {
                int b = stack.pop();
                int a = stack.pop();
                switch (token) {
                case "+":
                    stack.push(a + b);
                    break;
                case "-":
                    stack.push(a - b);
                    break;
                case "*":
                    stack.push(a * b);
                    break;
                case "/":
                    stack.push(a / b);
                    break;
                }
            } else {
                stack.push(Integer.parseInt(token));
            }
        }

        return stack.pop();
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: tokens = ["2","1","+","3","*"]
        // Expected: 9
        String[] tokens1 = {"2", "1", "+", "3", "*"};
        System.out.println("Output: " + solution.evalRPN(tokens1));

        // Example 2: tokens = ["4","13","5","/","+"]
        // Expected: 6
        String[] tokens2 = {"4", "13", "5", "/", "+"};
        System.out.println("Output: " + solution.evalRPN(tokens2));

        // Example 3: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
        // Expected: 22
        String[] tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
        System.out.println("Output: " + solution.evalRPN(tokens3));
    }
}
