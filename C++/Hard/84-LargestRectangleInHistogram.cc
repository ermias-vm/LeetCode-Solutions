#include <iostream>
#include <vector>
#include <stack>

using namespace std;


// Description: https://leetcode.com/problems/largest-rectangle-in-histogram/description/


// Approach: Monotonic Stack
/*
    Time complexity: O(n) - Each element is pushed and popped at most once.
    Space complexity: O(n) - Stack can contain at most n elements.

    We use a monotonic increasing stack to keep track of bar indices.
    For each bar, we pop bars from the stack that are taller than the current bar
    and calculate the area with the popped bar as the smallest (limiting) height.
    The width extends from the current index back to the index after the new stack top.
*/


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        int maxArea = 0;
        int n = heights.size();

        for (int i = 0; i <= n; i++) {
            int currHeight = (i == n) ? 0 : heights[i];

            while (!st.empty() && heights[st.top()] > currHeight) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            st.push(i);
        }

        return maxArea;
    }
};

// Test
int main() {
    Solution solution;
    vector<int> heights1 = {2, 1, 5, 6, 2, 3};
    vector<int> heights2 = {2, 4};

    cout << "Test case 1: " << solution.largestRectangleArea(heights1) << endl; // Output: 10
    cout << "Test case 2: " << solution.largestRectangleArea(heights2) << endl; // Output: 4

    return 0;
}
