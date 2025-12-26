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

#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                if (token == "+") st.push(a + b);
                else if (token == "-") st.push(a - b);
                else if (token == "*") st.push(a * b);
                else if (token == "/") st.push(a / b);
            } 
            else st.push(stoi(token));
        }
        return st.top();
    }
};

// Test
int main() {
    Solution sol;
    vector<string> tokens1 = {"2", "1", "+", "3", "*"};
    vector<string> tokens2 = {"4", "13", "5", "/", "+"};
    vector<string> tokens3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};

    cout << "Example 1: " << sol.evalRPN(tokens1) << endl; // Output: 9
    cout << "Example 2: " << sol.evalRPN(tokens2) << endl; // Output: 6
    cout << "Example 3: " << sol.evalRPN(tokens3) << endl; // Output: 22

    return 0;
}
