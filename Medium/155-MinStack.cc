#include <iostream>
#include <stack>

using namespace std;


// Description:  https://leetcode.com/problems/min-stack/description/


// Approach: Use two stacks, one for the elements and one for the minimums.

/* 
    Time complexity: O(1) for each operation

    Space complexity: O(n) where n is the number of elements in the stack

    Approach description: 
    We use two stacks to implement the MinStack class. The main stack stores all the elements, 
    while the minStack stores the minimum elements. When pushing a new element, we push it onto 
    the main stack. If the minStack is empty or the new element is less than or equal to the top 
    of the minStack, we also push it onto the minStack. When popping an element, we pop it from 
    both stacks if it is equal to the top of the minStack. The top operation returns the top of 
    the main stack, and the getMin operation returns the top of the minStack.
*/


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

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */


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

