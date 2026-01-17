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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(tokensSize * sizeof(int));
    int top = -1;

    for (int i = 0; i < tokensSize; i++) {
        char* token = tokens[i];
        // Check if it's an operator (single char and one of + - * /)
        if (strlen(token) == 1 &&
            (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
            int b = stack[top--];
            int a = stack[top--];
            int result;
            switch (token[0]) {
            case '+':
                result = a + b;
                break;
            case '-':
                result = a - b;
                break;
            case '*':
                result = a * b;
                break;
            case '/':
                result = a / b;
                break;
            }
            stack[++top] = result;
        } else {
            // It's a number (could be negative like "-11")
            stack[++top] = atoi(token);
        }
    }

    int result = stack[top];
    free(stack);
    return result;
}

// Test
int main() {
    // Example 1: tokens = ["2","1","+","3","*"]
    char* tokens1[] = {"2", "1", "+", "3", "*"};
    printf("Output: %d\n", evalRPN(tokens1, 5));

    // Example 2: tokens = ["4","13","5","/","+"]
    char* tokens2[] = {"4", "13", "5", "/", "+"};
    printf("Output: %d\n", evalRPN(tokens2, 5));

    // Example 3: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
    char* tokens3[] = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
    printf("Output: %d\n", evalRPN(tokens3, 13));

    return 0;
}
