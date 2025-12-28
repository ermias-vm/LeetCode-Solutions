// Description: https://leetcode.com/problems/3sum/description/

/*
    Approach: Sorting + Two Pointers

    Sort the array to enable two-pointer technique and duplicate handling.
    Fix one element and use two pointers to find pairs summing to its negation.
    Skip duplicate values for the fixed element to avoid repeated triplets.
    For valid triplets, also skip duplicates for the other two elements.
    Move pointers based on current sum: left++ if too small, right-- if too large.
    Continue until all elements have been considered as the fixed element.

    Time complexity: O(n^2) - O(n log n) sort + O(n^2) two-pointer search.
    Space complexity: O(1) - Excluding the output array.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;
        for (int i = 0; i < int(nums.size()); ++i) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;  // Skip duplicates

            int left = i + 1;
            int right = nums.size() - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum == 0) {
                    result.push_back({nums[i], nums[left], nums[right]});
                    while (left < right && nums[left] == nums[left + 1]) ++left;  // Skip duplicates
                    while (left < right && nums[right] == nums[right - 1])
                        --right;  // Skip duplicates
                    ++left;
                    --right;
                } else if (sum < 0)
                    ++left;
                else
                    --right;
            }
        }
        return result;
    }
};

// Test

void printResult(const vector<vector<int>>& result) {
    for (const auto& triplet : result) {
        for (int num : triplet) { cout << num << " "; }
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
