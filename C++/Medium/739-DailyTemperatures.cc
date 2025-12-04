#include <iostream>
#include <vector>
#include <stack>

using namespace std;


// Description: https://leetcode.com/problems/daily-temperatures/


// Approach: Monotonic Stack

/* 
    Time complexity: O(n)
    Space complexity: O(n)

    We use a monotonic decreasing stack that stores indices of temperatures.
    For each temperature, we pop all indices from the stack where the temperature
    is less than the current one, and calculate the difference in days.
    This ensures each element is pushed and popped at most once.
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> answer(n, 0);
        stack<int> st;  // Stack of indices
        
        for (int i = 0; i < n; i++) {
            while (!st.empty() && temperatures[st.top()] < temperatures[i]) {
                int prevIndex = st.top();
                st.pop();
                answer[prevIndex] = i - prevIndex;
            }
            st.push(i);
        }
        
        return answer;
    }
};


// Test
int main() {
    Solution sol;

    // Test case 1
    vector<int> temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> result1 = sol.dailyTemperatures(temps1);
    cout << "Test 1: [";
    for (unsigned int i = 0; i < result1.size(); i++) {
        cout << result1[i];
        if (i < result1.size() - 1) cout << ", ";
    }
    cout << "]" << endl;  // Expected: [1, 1, 4, 2, 1, 1, 0, 0]

    // Test case 2
    vector<int> temps2 = {30, 40, 50, 60};
    vector<int> result2 = sol.dailyTemperatures(temps2);
    cout << "Test 2: [";
    for (unsigned int i = 0; i < result2.size(); i++) {
        cout << result2[i];
        if (i < result2.size() - 1) cout << ", ";
    }
    cout << "]" << endl;  // Expected: [1, 1, 1, 0]

    // Test case 3
    vector<int> temps3 = {30, 60, 90};
    vector<int> result3 = sol.dailyTemperatures(temps3);
    cout << "Test 3: [";
    for (unsigned int i = 0; i < result3.size(); i++) {
        cout << result3[i];
        if (i < result3.size() - 1) cout << ", ";
    }
    cout << "]" << endl;  // Expected: [1, 1, 0]

    return 0;
}
