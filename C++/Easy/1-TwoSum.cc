// Description: https://leetcode.com/problems/two-sum/description/

/*
    Approach: Hash Map

    Use a hash map to store each number and its index as we iterate.
    For each element, calculate its complement (target - current number).
    Check if the complement already exists in the hash map.
    If found, return the complement's index and current index.
    Otherwise, store the current number and index in the map.
    This achieves single-pass lookup with O(1) average time per operation.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(n) - Hash map stores at most n elements.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (hash.find(complement) != hash.end()) { return {hash[complement], i}; }
            hash[nums[i]] = i;
        }
        return {};
    }
};

// Test
int main() {
    Solution solution;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> result = solution.twoSum(nums, target);
    if (!result.empty()) {
        cout << "Indices: " << result[0] << " and " << result[1] << endl;
    } else {
        cout << "No two sum solution found." << endl;
    }
    return 0;
}
