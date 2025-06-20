import java.util.Stack;

// Description: https://leetcode.com/problems/min-stack/description/

// Solution
class MinStack {
    private Stack<Integer> mainStack;
    private Stack<Integer> minStack;

    public MinStack() {
        mainStack = new Stack<>();
        minStack = new Stack<>();
    }
    
    public void push(int val) {
        mainStack.push(val);
        if (minStack.isEmpty() || val <= minStack.peek()) {
            minStack.push(val);
        }
    }
    
    public void pop() {
        if (mainStack.peek().equals(minStack.peek())) {
            minStack.pop();
        }
        mainStack.pop();
    }
    
    public int top() {
        return mainStack.peek();
    }
    
    public int getMin() {
        return minStack.peek();
    }
}

// Test
class Test {
    public static void main(String[] args) {
        MinStack minStack = new MinStack();
        
        System.out.println("Operations:");
        System.out.println("push(-2)");
        minStack.push(-2);
        
        System.out.println("push(0)");
        minStack.push(0);
        
        System.out.println("push(-3)");
        minStack.push(-3);
        
        System.out.println("getMin() -> " + minStack.getMin()); // return -3
        
        System.out.println("pop()");
        minStack.pop();
        
        System.out.println("top() -> " + minStack.top());       // return 0
        System.out.println("getMin() -> " + minStack.getMin()); // return -2
    }
}