#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


// Description:  https://leetcode.com/problems/3sum/description/


//  Approach (Two Pointers)  

/* 
    Time complexity: O(n^2), where n is the number of elements in the input array.
    Space complexity: O(1), ignoring the space required for the output.

    The approach involves sorting the array and then using a two-pointer 
    technique to find all unique triplets that sum up to zero.
    We iterate through it using a loop. In each iteration, we fix one element and 
    use two pointers to find the other two elements that, together with the fixed 
    element, sum up to zero. The first pointer (left) is initialized just after the 
    fixed element, and the second pointer (right) is initialized at the end of the array.

    We then calculate the sum of the three elements: the fixed element, the element pointed 
    to by left, and the element pointed to by right. If the sum is zero, we have found a 
    valid triplet and add it to the list of results. We then move both pointers to search 
    for more possible triplets. If the sum is less than zero, we increment the left pointer 
    to increase the sum. If the sum is greater than zero, we decrement the right pointer to decrease the sum.

    To avoid duplicates, we skip over duplicate elements for both the fixed element and the elements pointed to by left and right
*/



class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        for (int i = 0; i < int(nums.size()); ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicates
            
            int left = i + 1;
            int right = nums.size() - 1;
            
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                
                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) ++left; // Skip duplicates
                    while (left < right && nums[right] == nums[right - 1]) --right; // Skip duplicates
                    ++left; 
                    --right;
                } 
                else if (sum < 0) ++left;
                else --right;
            }
        }
        return result;
    }
};


// Test

void printResult(const vector<vector<int>>& result) {
    for (const auto& triplet : result) {
        for (int num : triplet) {
            cout << num << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    Solution sol;
    vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
    vector<int> nums2 = {0, 1, 1};
    vector<int> nums3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    // Print results
    printResult(sol.threeSum(nums1));
    printResult(sol.threeSum(nums2));
    printResult(sol.threeSum(nums3));

    return 0;
}
