#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <climits>

using namespace std;



// Description:  https://leetcode.com/problems/median-of-two-sorted-arrays/description/



/*
    Solution:

    Time complexity: O(log(min(m, n)))

    Space complexity: O(1)
    
*/



using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // If nums1 is larger than nums2, swap them to make sure nums1 is the smaller array.
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
        // x and y are the sizes of nums1 and nums2, respectively.
        int x = nums1.size();
        int y = nums2.size();
        // low and high pointers for binary search in nums1.
        int low = 0, high = x;
        
        // Binary search begins.
        while (low <= high) {
            // partitionX and partitionY divide nums1 and nums2 into left and right halves.
            int partitionX = (low + high) / 2;
            // Ensures left and right halves have equal total elements or one more on the left if odd total.
            int partitionY = (x + y + 1) / 2 - partitionX;
            
            // maxLeftX and minRightX are the edge values of the left and right halves of nums1.
            int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
            int minRightX = (partitionX == x) ? INT_MAX : nums1[partitionX];
            
            // maxLeftY and minRightY are the edge values of the left and right halves of nums2.
            int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
            int minRightY = (partitionY == y) ? INT_MAX : nums2[partitionY];
            
            // Check if we have found the correct partition.
            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                // If total number of elements is even, average the middle two elements.
                if ((x + y) % 2 == 0) return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                // If odd, return the middle element.
                else return max(maxLeftX, maxLeftY);
            }   
            // If not partitioned correctly, adjust the binary search bounds.
            else if (maxLeftX > minRightY) high = partitionX - 1; // Move partitionX left.
            else low = partitionX + 1; // Move partitionX right.
        }
        // If the loop exits without returning, the inputs were invalid.
        throw invalid_argument("Input arrays are not sorted or have incorrect sizes.");
    }
};


/*
    Submission   94.82% faster than other C++ submissions (24/06/2024):


class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }
        
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
                if ((x + y) % 2 == 0) return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                else return max(maxLeftX, maxLeftY);
            }   
            else if (maxLeftX > minRightY) high = partitionX - 1;
            else low = partitionX + 1;
        }
        throw invalid_argument("Input arrays are not sorted or have incorrect sizes.");
    }
};


*/


//Test
int main() {
    Solution solution;
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2};
    cout << "Example 1: " << solution.findMedianSortedArrays(nums1, nums2) << endl;

    nums1 = {1, 2};
    nums2 = {3, 4};
    cout << "Example 2: " << solution.findMedianSortedArrays(nums1, nums2) << endl;

    return 0;
}
