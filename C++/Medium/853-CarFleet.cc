// Description: https://leetcode.com/problems/car-fleet/description/

/*
    Approach: Sorting + Monotonic Stack

    Calculate the time each car needs to reach the target: time = (target - position) / speed.
    Pair each car's position with its arrival time.
    Sort cars by position in descending order (closest to target first).
    Use a stack to track distinct fleets based on arrival times.
    If a car takes more time than the car ahead, it forms a new fleet.
    If it takes less or equal time, it catches up and merges with the fleet ahead.

    Time complexity: O(n log n) - Due to sorting.
    Space complexity: O(n) - For storing car pairs and stack.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, double>> cars(n);  // {position, time to reach target}

        for (int i = 0; i < n; i++) {
            cars[i] = {position[i], (double)(target - position[i]) / speed[i]};
        }

        // Sort by position in descending order (closest to target first)
        sort(cars.begin(), cars.end(), [](auto& a, auto& b) { return a.first > b.first; });

        stack<double> st;  // Stack of arrival times

        for (int i = 0; i < n; i++) {
            double time = cars[i].second;
            // If current car takes more time, it forms a new fleet
            if (st.empty() || time > st.top()) {
                st.push(time);
            }
            // Otherwise, it catches up and joins the fleet ahead
        }

        return st.size();
    }
};

// Test
int main() {
    Solution sol;

    // Example 1: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
    vector<int> pos1 = {10, 8, 0, 5, 3};
    vector<int> speed1 = {2, 4, 1, 1, 3};
    cout << "Output: " << sol.carFleet(12, pos1, speed1) << endl;

    // Example 2: target = 10, position = [3], speed = [3]
    vector<int> pos2 = {3};
    vector<int> speed2 = {3};
    cout << "Output: " << sol.carFleet(10, pos2, speed2) << endl;

    // Example 3: target = 100, position = [0,2,4], speed = [4,2,1]
    vector<int> pos3 = {0, 2, 4};
    vector<int> speed3 = {4, 2, 1};
    cout << "Output: " << sol.carFleet(100, pos3, speed3) << endl;

    return 0;
}
