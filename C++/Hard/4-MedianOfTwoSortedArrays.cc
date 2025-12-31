// Description: https://leetcode.com/problems/median-of-two-sorted-arrays/description/

/*
    Approach: Binary Search on Smaller Array

    Binary search on the smaller array to find the correct partition point.
    The partition divides both arrays such that left elements <= right elements.
    Use INT_MIN and INT_MAX to handle edge cases at array boundaries.
    For valid partition: maxLeftX <= minRightY and maxLeftY <= minRightX.
    If total length is even, median = (max(lefts) + min(rights)) / 2.
    If odd, median = max(lefts). Adjust partition based on comparison.

    Time complexity: O(log(min(m, n))) - Binary search on smaller array.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <climits>
#include <iomanip>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) { return findMedianSortedArrays(nums2, nums1); }

        int x = nums1.size();
        int y = nums2.size();
        int low = 0, high = x;

        while (low <= high) {
            int partitionX = (low + high) / 2;
            int partitionY = (x + y + 1) / 2 - partitionX;

            int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int minRightX = (partitionX == x) ? INT_MAX : nums1[partitionX];

            int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            int minRightY = (partitionY == y) ? INT_MAX : nums2[partitionY];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((x + y) % 2 == 0)
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                else
                    return max(maxLeftX, maxLeftY);
            } else if (maxLeftX > minRightY)
                high = partitionX - 1;
            else
                low = partitionX + 1;
        }
        throw invalid_argument("Input arrays are not sorted or have incorrect sizes.");
    }
};

// Test
int main() {
    Solution solution;
    
    // Example 1: nums1 = [1,3], nums2 = [2]
    vector<int> nums1a = {1, 3};
    vector<int> nums2a = {2};
    cout << "Output: " << fixed << setprecision(5) << solution.findMedianSortedArrays(nums1a, nums2a) << endl;

    // Example 2: nums1 = [1,2], nums2 = [3,4]
    vector<int> nums1b = {1, 2};
    vector<int> nums2b = {3, 4};
    cout << "Output: " << fixed << setprecision(5) << solution.findMedianSortedArrays(nums1b, nums2b) << endl;

    return 0;
}
