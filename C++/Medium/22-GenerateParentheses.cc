// Description: https://leetcode.com/problems/generate-parentheses/description/

/*
    Approach: Iterative with Stack

    Use a stack to track generation states (current string, open count, close count).
    For each state, generate new states by adding '(' or ')' if valid.
    Can add '(' if open count < n (haven't used all opening brackets).
    Can add ')' if close count < open count (maintain balance).
    When string length reaches 2*n, it's a complete valid combination.
    Continue until stack is empty (all combinations generated).

    Time complexity: O(4^n / sqrt(n)) - Catalan number growth.
    Space complexity: O(4^n / sqrt(n)) - Stack and result storage.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(unsigned int n) {
        vector<string> result;
        stack<pair<string, pair<unsigned int, unsigned int>>> stk;
        stk.push({"", {0, 0}});

        while (!stk.empty()) {
            auto [current, counts] = stk.top();
            stk.pop();
            unsigned int open = counts.first;
            unsigned int close = counts.second;

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

// Test

void print(const vector<string>& result) {
    cout << "Output: [";
    for (size_t i = 0; i < result.size(); i++) {
        cout << "\"" << result[i] << "\"";
        if (i < result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // Example 1: n = 3
    vector<string> res1 = solution.generateParenthesis(3);
    // Sort for consistent output
    sort(res1.begin(), res1.end());
    print(res1);

    // Example 2: n = 1
    vector<string> res2 = solution.generateParenthesis(1);
    print(res2);

    return 0;
}
