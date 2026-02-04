// Description: https://leetcode.com/problems/car-fleet/description/

/*
    Approach: Sorting + Monotonic Stack

    Calculate the time each car needs to reach the target: time = (target - position) / speed.
    Pair each car's position with its arrival time.
    Sort cars by position in descending order (closest to target first).
    Use a stack to track distinct fleets based on arrival times.
    If a car takes more time than the car ahead, it forms a new fleet.
    If it takes less time, it catches up and merges with the fleet ahead.

    Time complexity: O(n log n) - Due to sorting.
    Space complexity: O(n) - For storing car pairs and stack.
*/

import java.util.*;

class Solution {
    public int carFleet(int target, int[] position, int[] speed) {
        int n = position.length;
        if (n == 0) return 0;

        // Create array of [position, time to reach target]
        double[][] cars = new double[n][2];
        for (int i = 0; i < n; i++) {
            cars[i][0] = position[i];
            cars[i][1] = (double)(target - position[i]) / speed[i];
        }

        // Sort by position in descending order
        Arrays.sort(cars, (a, b) -> Double.compare(b[0], a[0]));

        Deque<Double> stack = new ArrayDeque<>();
        for (double[] car : cars) {
            double time = car[1];
            // If current car takes more time, it forms a new fleet
            if (stack.isEmpty() || time > stack.peek()) {
                stack.push(time);
            }
            // Otherwise, it catches up and joins the fleet ahead
        }

        return stack.size();
    }
}

// Test
class Test {
    public static void main(String[] args) {
        Solution solution = new Solution();

        // Example 1: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
        // Expected: 3
        int[] pos1 = {10, 8, 0, 5, 3};
        int[] speed1 = {2, 4, 1, 1, 3};
        System.out.println("Output: " + solution.carFleet(12, pos1, speed1));

        // Example 2: target = 10, position = [3], speed = [3]
        // Expected: 1
        int[] pos2 = {3};
        int[] speed2 = {3};
        System.out.println("Output: " + solution.carFleet(10, pos2, speed2));

        // Example 3: target = 100, position = [0,2,4], speed = [4,2,1]
        // Expected: 1
        int[] pos3 = {0, 2, 4};
        int[] speed3 = {4, 2, 1};
        System.out.println("Output: " + solution.carFleet(100, pos3, speed3));
    }
}
