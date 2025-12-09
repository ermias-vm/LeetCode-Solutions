#include <iostream>
#include <vector>

using namespace std;


// Description: https://leetcode.com/problems/binary-search/description/


// Approach: Binary Search
/*
    Time complexity: O(log n) - We divide the search space in half each iteration.
    Space complexity: O(1) - We use a constant amount of extra space.

    We use two pointers to define the search range.
    At each step, we compare the middle element with the target.
    If the middle element equals the target, we return its index.
    If the target is greater, we search the right half.
    If the target is smaller, we search the left half.
*/


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
    vector<int> nums1 = {-1, 0, 3, 5, 9, 12};
    vector<int> nums2 = {-1, 0, 3, 5, 9, 12};

    cout << "Test case 1: " << solution.search(nums1, 9) << endl;  // Output: 4
    cout << "Test case 2: " << solution.search(nums2, 2) << endl;  // Output: -1

    return 0;
}
