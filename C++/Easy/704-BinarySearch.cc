// Description: https://leetcode.com/problems/binary-search/description/

/*
    Approach: Binary Search

    Use two pointers (left and right) to define the search range.
    Calculate the middle index using: mid = left + (right - left) / 2 to avoid overflow.
    Compare the middle element with the target value.
    If equal, return the index. If target is greater, search the right half.
    If target is smaller, search the left half.
    Repeat until the target is found or search space is exhausted.

    Time complexity: O(log n) - Search space halves each iteration.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return -1;
    }
};

// Test
int main() {
    Solution solution;
    
    // Example 1: nums = [-1,0,3,5,9,12], target = 9
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    cout << "Output: " << solution.search(nums1, 9) << endl;
    
    // Example 2: nums = [-1,0,3,5,9,12], target = 2
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};
    cout << "Output: " << solution.search(nums2, 2) << endl;

    return 0;
}
