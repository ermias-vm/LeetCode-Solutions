// Description: https://leetcode.com/problems/valid-parentheses/description/

/*
    Approach: Stack with Hash Map

    Use a stack to track opening brackets encountered during iteration.
    Store bracket pairs in a hash map for O(1) matching lookups.
    For each opening bracket, push it onto the stack.
    For each closing bracket, check if stack is non-empty and top matches.
    If mismatch or stack empty on closing bracket, return false.
    After processing, stack should be empty for valid parentheses.

    Time complexity: O(n) - Single pass through the string.
    Space complexity: O(n) - Stack stores at most n/2 opening brackets.
*/

#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> openedBrackets;
        unordered_map<char, char> bracketMap = {{')', '('}, {']', '['}, {'}', '{'}};

        for (char c : s) {
            if (bracketMap.find(c) != bracketMap.end()) {
                if (openedBrackets.empty() || openedBrackets.top() != bracketMap[c]) return false;
                openedBrackets.pop();
            } else
                openedBrackets.push(c);
        }

        return openedBrackets.empty();
    }
};

// Test
int main() {
    Solution solution;
    
    // Example 1: s = "()"
    cout << "Output: " << (solution.isValid("()") ? "true" : "false") << endl;
    
    // Example 2: s = "()[]{}"
    cout << "Output: " << (solution.isValid("()[]{}") ? "true" : "false") << endl;
    
    // Example 3: s = "(]"
    cout << "Output: " << (solution.isValid("(]") ? "true" : "false") << endl;
    
    // Example 4: s = "([])"
    cout << "Output: " << (solution.isValid("([])") ? "true" : "false") << endl;
    
    // Example 5: s = "([)]"
    cout << "Output: " << (solution.isValid("([)]") ? "true" : "false") << endl;

    return 0;
}
