#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Description:  https://leetcode.com/problems/generate-parentheses/description/

// Approach 1: Iterative using a stack

/* 
    Time complexity: O(4^n / sqrt(n))

    Space complexity: O(4^n / sqrt(n))

    The approach uses an iterative method with a stack to generate all valid combinations of parentheses. 
    Each state in the stack contains the current string, the count of open parentheses, and the 
    count of close parentheses. 
    We start with an initial state and iteratively generate new states by adding open or close 
    parentheses while maintaining the balance.
    Valid combinations are added to the result list when the length of the current string reaches 2*n.
*/

class Solution {
public:
    vector<string> generateParenthesis(unsigned int n) {
        vector <string> result;
        stack<pair<string, pair<unsigned int, unsigned int>>> stk;
        stk.push({"", {0, 0}});
        
        while (!stk.empty()) {
            auto[current, counts] = stk.top();
            stk.pop();
            unsigned int  open = counts.first;
            unsigned int  close = counts.second;

            if (current.size() == n * 2) {
                result.push_back(current);
                continue;
            }

            if (open < n) stk.push({current + "(", {open + 1, close}});
            if (open > close) stk.push({current + ")", {open, close + 1}});
        }
        return result;
    }
};


//-------------------------------------------------------------------------


// Approach 2: Backtracking

/* 
    Time complexity: O(4^n / sqrt(n))

    Space complexity: O(4^n / sqrt(n))

    The approach uses backtracking to generate all valid combinations of parentheses. 
    We maintain a balance of open and close parentheses. 
    We start with an empty string and add open parentheses until we reach the limit of n. 
    Then, we add close parentheses as long as they do not exceed the number of open parentheses. 
    This ensures that the parentheses are well-formed. 
    The recursion explores all possible combinations, and valid combinations are added to the result list.
*/


class Solution2 {

public:
    vector<string> generateParenthesis(unsigned int n) {
        vector<string> result;
        generate(result, "", 0, 0, n);
        return result;
    }

private:
    void generate(vector<string>& result, string current, unsigned int open, unsigned int close, unsigned int n) {
        if (current.size() == n * 2) {
            result.push_back(current);
            return;
        }

        if (open < n) generate (result, current + "(", open + 1, close, n);
        if (close < open) generate (result, current + ")", open, close + 1, n);
    }
};


// Test

void print (const vector<string>& result) {
    for (const string& s : result) {
        cout << s << endl;
    }
    cout << endl;
}

int main() {
    Solution solution;
    Solution2 solution2;
    
    print(solution.generateParenthesis(3)); // Approach 1 : (iterative using stack)
    print(solution2.generateParenthesis(3)); // Approach 2 : (bactraking)

    return 0;
}