#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Description: https://leetcode.com/problems/valid-parentheses

// Approach: Stack
bool isValid(char* s) {
    int n = (int)strlen(s);
    char stack[n];
    int top = -1;

    for (int i = 0; i < n; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else {
            // If stack is empty or top bracket doesn't match, invalid
            if (top < 0) return false;
            if ((c == ')' && stack[top] != '(') ||
                (c == '}' && stack[top] != '{') ||
                (c == ']' && stack[top] != '[')) {
                return false;
            }
            top--; // pop
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