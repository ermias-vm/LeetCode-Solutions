#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

// Description: https://leetcode.com/problems/contains-duplicate

/*
    Time complexity: O(n)
    Space complexity: O(n)
    
    Use hash set to track seen numbers. For each number, check if already seen 
    (return true if duplicate found), otherwise add to set. Return false if no duplicates.
*/

// Solution
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen; // Create an empty unordered set to keep track of seen numbers.
        for (int num : nums) { // Iterate through each number in the input vector.
            if (seen.find(num) != seen.end()) return true; // If the current number is already in the set, return true (duplicate found).
            seen.insert(num); // If not, insert the current number into the set.
        }
        return false; // If no duplicates are found after checking all numbers, return false.
    }
};

// Test
int main() {
    Solution solution;
    vector<int> nums1 = {1,2,3,1};
    cout << "Test 1 (Expected: 1): " << solution.containsDuplicate(nums1) << endl;

    vector<int> nums2 = {1,2,3,4};
    cout << "Test 2 (Expected: 0): " << solution.containsDuplicate(nums2) << endl;

    vector<int> nums3 = {1,1,1,3,3,4,3,2,4,2};
    cout << "Test 3 (Expected: 1): " << solution.containsDuplicate(nums3) << endl;

    return 0;
}
