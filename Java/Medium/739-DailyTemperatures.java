// Description: https://leetcode.com/problems/daily-temperatures/description/

/*
    Approach: Monotonic Stack

    Use a monotonic decreasing stack that stores indices of temperatures.
    For each new temperature, pop indices from the stack while current temp is warmer.
    For each popped index, calculate the wait time as (current_index - popped_index).
    Push the current index onto the stack after processing.
    Elements remaining in the stack have no warmer day (answer stays 0).
    Each element is pushed and popped at most once.

    Time complexity: O(n) - Single pass with constant time operations per element.
    Space complexity: O(n) - Stack can contain at most n indices.
*/

import java.util.*;

class Solution {
    public int[] dailyTemperatures(int[] temperatures) {
        int n = temperatures.length;
        int[] answer = new int[n];
        Deque<Integer> stack = new ArrayDeque<>();

        for (int i = 0; i < n; i++) {
            while (!stack.isEmpty() && temperatures[stack.peek()] < temperatures[i]) {
                int prevIndex = stack.pop();
                answer[prevIndex] = i - prevIndex;
            }
            stack.push(i);
        }

        return answer;
    }
}

// Test
class Test {
    public static String formatArray(int[] arr) {
        StringBuilder sb = new StringBuilder("[");
        for (int i = 0; i < arr.length; i++) {
            sb.append(arr[i]);
            if (i < arr.length - 1) sb.append(", ");
        }
        sb.append("]");
        return sb.toString();
    }

    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: temperatures = [73,74,75,71,69,72,76,73]
        // Expected: [1, 1, 4, 2, 1, 1, 0, 0]
        int[] temps1 = {73, 74, 75, 71, 69, 72, 76, 73};
        System.out.println("Output: " + formatArray(solution.dailyTemperatures(temps1)));

        // Example 2: temperatures = [30,40,50,60]
        // Expected: [1, 1, 1, 0]
        int[] temps2 = {30, 40, 50, 60};
        System.out.println("Output: " + formatArray(solution.dailyTemperatures(temps2)));

        // Example 3: temperatures = [30,60,90]
        // Expected: [1, 1, 0]
        int[] temps3 = {30, 60, 90};
        System.out.println("Output: " + formatArray(solution.dailyTemperatures(temps3)));
    }
}
