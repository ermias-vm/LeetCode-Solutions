// Description: https://leetcode.com/problems/container-with-most-water/description/

/*
    Approach: Two Pointers

    Start with pointers at both ends for maximum width container.
    Calculate area as min(height[left], height[right]) * (right - left).
    Move the pointer with smaller height inward to potentially find larger area.
    This greedy choice ensures we don't miss the optimal solution.
    Track the maximum area found during the iteration.
    Continue until both pointers meet.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer and area variables used.
*/

#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int maxArea(vector<int>& height) {
        unsigned int left = 0; 
        unsigned right = height.size() - 1;
        unsigned int maxArea = 0;
        
        while (left < right) {
            unsigned int width = right - left;
            unsigned int currentHeight = min(height[left], height[right]);
            unsigned int currentArea = width * currentHeight;
            maxArea = max(maxArea, currentArea);

            if (height[left] < height[right]) left++;
            else right--;
        }
        
        return maxArea;
    }
};



// Test
int main() {
    Solution solution;
    vector<int> height1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    vector<int> height2 = {1, 1};

    cout << "Test case 1: " << solution.maxArea(height1) << endl; // Output: 49
    cout << "Test case 2: " << solution.maxArea(height2) << endl; // Output: 1

    return 0;
}
