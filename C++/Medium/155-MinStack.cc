// Description: https://leetcode.com/problems/min-stack/description/

/*
    Approach: Two Stacks

    Use a main stack to store all elements pushed.
    Use a separate min stack to track minimum values at each state.
    Push to min stack only when value is <= current minimum.
    When popping, also pop from min stack if values match.
    getMin() returns top of min stack in O(1) time.
    This design maintains minimum tracking through push/pop operations.

    Time complexity: O(1) - All operations are constant time.
    Space complexity: O(n) - Two stacks store at most n elements each.
*/

#include <iostream>
#include <stack>

using namespace std;


class MinStack {
private:
    stack<int> mainStack;
    stack<int> minStack;

public:
    MinStack() {
        
    }
    
    void push(int val) {
        mainStack.push(val);
        if (minStack.empty() || val <= minStack.top()) minStack.push(val);
    }
    
    void pop() {
        if (mainStack.top() == minStack.top()) minStack.pop();
        mainStack.pop();
    }
    
    int top() {
        return mainStack.top();
    }
    
    int getMin() {
        return minStack.top();
    }
};

// Test
int main() {
    MinStack stk;
    stk.push(-2);
    stk.push(0);
    stk.push(-3);
    cout << stk.getMin() << endl; // return -3
    stk.pop();
    cout << stk.top() << endl;    // return 0
    cout << stk.getMin() << endl; // return -2

    return 0;
}

