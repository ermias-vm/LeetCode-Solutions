#include <iostream>
#include <vector>
#include <stack>
#include <string>


#include <unordered_map> // Approach 2
#include <functional>    // Approach 2

using namespace std;


// Description: https://leetcode.com/problems/evaluate-reverse-polish-notation/


// Approach 1 : Use a stack to evaluate the expression

/* 
    Time complexity: O(n)
    Space complexity: O(n)

    The approach involves iterating through the tokens and using a stack to keep track of operands. 
    For each token, if it is an operator, we pop the top two elements from the stack, apply the operator, 
    and push the result back onto the stack. If it is an operand, we push it onto the stack. 
    This ensures that we evaluate the expression in the correct order. 
    The time complexity is O(n) because we process each token once, and the space complexity is O(n) 
    because in the worst case, we might push all tokens onto the stack.
*/

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



// ----------------------------------------------------------------------


// Approach 2: Use an unordered_map to store the operators and their corresponding lambda functions

/* 
    Time complexity: O(n)
    Space complexity: O(n)

    Iterate through the tokens, and for each token, check if it is an operator using the map. 
    If it is an operator, pop the top two elements from the stack, apply the operator, and push the result back onto the stack. 
    If it is not an operator, convert it to an integer and push it onto the stack. 
    At the end, the stack will contain the result of the RPN expression.
*/


class Solution2 {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        unordered_map<string, function<int(int, int)>> ops = {
            {"+", [](int a, int b) { return a + b; }},
            {"-", [](int a, int b) { return a - b; }},
            {"*", [](int a, int b) { return a * b; }},
            {"/", [](int a, int b) { return a / b; }}
        };

        for (const string& token : tokens) {
            auto it = ops.find(token);
            if (it != ops.end()) {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                st.push(it->second(a, b));
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
