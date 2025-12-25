#include <iostream>
#include <vector>

using namespace std;

// Description: https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/

// Approach: Binary Search
// Compare mid element with the rightmost element.
// If nums[mid] > nums[right], the minimum is in the right half.
// Otherwise, the minimum is in the left half (including mid).

/* 
    Time complexity: O(log n) - Binary search.
    Space complexity: O(1) - We use a constant amount of extra space.
*/


class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[right]) left = mid + 1;
            else right = mid;
        }
        
        return nums[left];
    }
};



// Test
int main() {
    Solution solution;
    
    vector<int> nums1 = {3, 4, 5, 1, 2};
    cout << "Test case 1: " << solution.findMin(nums1) << endl; // Output: 1
    
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    cout << "Test case 2: " << solution.findMin(nums2) << endl; // Output: 0
    
    vector<int> nums3 = {11, 13, 15, 17};
    cout << "Test case 3: " << solution.findMin(nums3) << endl; // Output: 11

    return 0;
}
