// Description: https://leetcode.com/problems/contains-duplicate/description/

/*
    Approach: Hash Set

    Use an unordered_set to track numbers seen during iteration.
    For each number, check if it already exists in the set.
    If found, return true immediately as a duplicate exists.
    Otherwise, add the number to the set and continue.
    If iteration completes without finding duplicates, return false.
    Hash set provides O(1) average time for insertion and lookup.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(n) - Hash set stores at most n elements.
*/

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.find(num) != seen.end()) return true;
            seen.insert(num);
        }
        return false;
    }
};

// Test
int main() {
    Solution solution;
    
    // Example 1: nums = [1,2,3,1]
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Output: " << (solution.containsDuplicate(nums1) ? "true" : "false") << endl;
    
    // Example 2: nums = [1,2,3,4]
    vector<int> nums2 = {1, 2, 3, 4};
    cout << "Output: " << (solution.containsDuplicate(nums2) ? "true" : "false") << endl;
    
    // Example 3: nums = [1,1,1,3,3,4,3,2,4,2]
    vector<int> nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    cout << "Output: " << (solution.containsDuplicate(nums3) ? "true" : "false") << endl;

    return 0;
}
