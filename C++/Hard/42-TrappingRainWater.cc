#include <iostream>
#include <vector>

using namespace std;


// Description:  https://leetcode.com/problems/trapping-rain-water/


// Approach: Two-pointer technique
/* 
    Time complexity: O(n) - We traverse the array only once.
    Space complexity: O(1) - We use a constant amount of extra space.

   // Approach: Two-pointer technique
    // We use two pointers, one starting from the beginning and one from the end of the array.
    // We keep track of the maximum height seen so far from both ends.
    // We calculate the trapped water at each position by comparing the current height with the maximum height seen so far.


*/



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
    vector<int> height1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    vector<int> height2 = {4, 2, 0, 3, 2, 5};

    cout << "Test case 1: " << solution.trap(height1) << endl; // Output: 6
    cout << "Test case 2: " << solution.trap(height2) << endl; // Output: 9

    return 0;
}
