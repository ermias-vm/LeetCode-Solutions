// Description: https://leetcode.com/problems/trapping-rain-water/description/

/*
    Approach: Two Pointers

    Use two pointers starting from both ends of the height array.
    Maintain the maximum height seen from left and right sides.
    At each step, move the pointer with the smaller height inward.
    Water trapped at current position = max_height_from_side - current_height.
    Only count water if current height is less than the max from that side.
    Continue until both pointers meet.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer and max height variables used.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) return 0;

        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int water_trapped = 0;

        while (left < right) {
            if (height[left] < height[right]) {
                if (height[left] >= left_max) left_max = height[left];
                else water_trapped += left_max - height[left];
                left++;
            } else {
                if (height[right] >= right_max) right_max = height[right];
                else water_trapped += right_max - height[right];
                right--;
            }
        }

        return water_trapped;
    }
};

// Test
int main() {
    Solution solution;

    // Example 1: height = [0,1,0,2,1,0,1,3,2,1,2,1]
    vector<int> height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "Output: " << solution.trap(height1) << endl;

    // Example 2: height = [4,2,0,3,2,5]
    vector<int> height2 = {4, 2, 0, 3, 2, 5};
    cout << "Output: " << solution.trap(height2) << endl;

    return 0;
}
