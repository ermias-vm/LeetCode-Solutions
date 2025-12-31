// Description: https://leetcode.com/problems/daily-temperatures/description/

/*
    Approach: Monotonic Stack

    Use a monotonic decreasing stack that stores indices of temperatures.
    For each new temperature, pop indices from stack while current temp is warmer.
    For each popped index, calculate wait time as (current_index - popped_index).
    Push current index onto stack after processing.
    Elements remaining in stack have no warmer day (answer stays 0).
    Each element is pushed and popped at most once.

    Time complexity: O(n) - Each element pushed and popped at most once.
    Space complexity: O(n) - Stack can contain at most n indices.
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

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
void printVector(const vector<int>& v) {
    cout << "Output: [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution sol;

    // Example 1: temperatures = [73,74,75,71,69,72,76,73]
    vector<int> temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
    printVector(sol.dailyTemperatures(temps1));

    // Example 2: temperatures = [30,40,50,60]
    vector<int> temps2 = {30, 40, 50, 60};
    printVector(sol.dailyTemperatures(temps2));

    // Example 3: temperatures = [30,60,90]
    vector<int> temps3 = {30, 60, 90};
    printVector(sol.dailyTemperatures(temps3));

    return 0;
}
