#include <iostream>
#include <stack>
#include <unordered_map>

using namespace std;


// Description:  https://leetcode.com/problems/valid-parentheses/


// Approach: Stack

// When encountering a closing bracket, check if it matches the top of the stack.

/* 
    Time complexity: O(n) - We traverse the string once.
    Space complexity: O(n) - In the worst case, we store all opening brackets in the stack.


    Use a stack to keep track of opening brackets. 
    When encountering a closing bracket, check if it matches the top of the stack.
    If it matches, pop the top of the stack. If it doesn't match or the stack is empty, the string is invalid.
    After processing all characters, if the stack is empty, the string is valid; otherwise, it is invalid.
*/

class Solution {
public:
    bool isValid(string s) {
        stack<char> openedBrackets;
        unordered_map<char, char> bracketMap = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        for (char c : s) {
            if (bracketMap.find(c) != bracketMap.end()) { // closed bracket case
                if (openedBrackets.empty()|| openedBrackets.top() != bracketMap[c]) return false;
                openedBrackets.pop();
            }
            else  openedBrackets.push(c);
        }
        
        return openedBrackets.empty();
    }
};


//Test
int main() {
    Solution solution;
    string test1 = "()";
    string test2 = "()[]{}";
    string test3 = "(]";

    cout << "Test case 1: " << (solution.isValid(test1) ? "true" : "false") << endl; // Output: true
    cout << "Test case 2: " << (solution.isValid(test2) ? "true" : "false") << endl; // Output: true
    cout << "Test case 3: " << (solution.isValid(test3) ? "true" : "false") << endl; // Output: false


}

