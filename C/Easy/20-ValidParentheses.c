// Description: https://leetcode.com/problems/valid-parentheses/description/

/*
    Approach: Stack

    Use a stack to track opening brackets as we iterate through the string.
    For each opening bracket, push it onto the stack.
    For each closing bracket, check if it matches the top of the stack.
    If the stack is empty or brackets don't match, return false.
    After processing all characters, the stack should be empty for valid input.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(n) - Stack stores at most n/2 opening brackets.
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
bool isValid(char* s) {
    int n = (int)strlen(s);
    char stack[n];
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else {
            if (top < 0) return false;
            if ((c == ')' && stack[top] != '(') ||
                (c == '}' && stack[top] != '{') ||
                (c == ']' && stack[top] != '[')) {
                return false;
            }
            top--;
        }
    }
    return (top == -1);
}

// Test
int main(void) {
    char* s = "()";
    printf("Input: s = \"%s\"\n", s);
    printf("Output: %s\n", isValid(s) ? "true" : "false");

    s = "()[]{}";
    printf("\nInput: s = \"%s\"\n", s);
    printf("Output: %s\n", isValid(s) ? "true" : "false");

    s = "(]";
    printf("\nInput: s = \"%s\"\n", s);
    printf("Output: %s\n", isValid(s) ? "true" : "false");

    s = "([{}])";
    printf("\nInput: s = \"%s\"\n", s);
    printf("Output: %s\n", isValid(s) ? "true" : "false");

    s = "[(])";
    printf("\nInput: s = \"%s\"\n", s);
    printf("Output: %s\n", isValid(s) ? "true" : "false");

    return 0;
}