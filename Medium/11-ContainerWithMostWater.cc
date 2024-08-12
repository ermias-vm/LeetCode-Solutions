#include <iostream>
#include <vector>

using namespace std;

// Description: https://leetcode.com/problems/container-with-most-water/

// Approach: Two-pointer technique
// We start with two pointers, one at the beginning and one at the end of the array.
// We calculate the area formed between the lines at these two pointers.
// We then move the pointer pointing to the shorter line inward, and repeat the process until the pointers meet.

/* 
    Time complexity: O(n) - We traverse the array only once.
    Space complexity: O(1) - We use a constant amount of extra space.
*/


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
