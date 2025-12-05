#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


// Description: https://leetcode.com/problems/car-fleet/description/


// Approach: Sort by position and use monotonic stack

/* 
    Time complexity: O(n log n)
    Space complexity: O(n)

    1. Pair each car's position with its time to reach target: time = (target - position) / speed
    2. Sort cars by position in descending order (closest to target first)
    3. Use a stack to track fleets: if a car takes more time than the car ahead,
       it forms a new fleet (can't catch up). Otherwise, it joins the fleet ahead.
*/

class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = position.size();
        vector<pair<int, double>> cars(n);  // {position, time to reach target}
        
        for (int i = 0; i < n; i++) {
            cars[i] = {position[i], (double)(target - position[i]) / speed[i]};
        }
        
        // Sort by position in descending order (closest to target first)
        sort(cars.begin(), cars.end(), [](auto& a, auto& b) {
            return a.first > b.first;
        });
        
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

    // Test case 1
    vector<int> pos1 = {10, 8, 0, 5, 3};
    vector<int> speed1 = {2, 4, 1, 1, 3};
    cout << "Test 1: " << sol.carFleet(12, pos1, speed1) << endl;  // Expected: 3

    // Test case 2
    vector<int> pos2 = {3};
    vector<int> speed2 = {3};
    cout << "Test 2: " << sol.carFleet(10, pos2, speed2) << endl;  // Expected: 1

    // Test case 3
    vector<int> pos3 = {0, 2, 4};
    vector<int> speed3 = {4, 2, 1};
    cout << "Test 3: " << sol.carFleet(100, pos3, speed3) << endl;  // Expected: 1

    return 0;
}
