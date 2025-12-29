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
void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]";
}

void runTest(vector<int> nums, int target) {
    Solution solution;
    vector<int> result = solution.twoSum(nums, target);
    
    cout << "Input: nums = ";
    printVector(nums);
    cout << ", target = " << target << endl;
    
    cout << "Output: ";
    printVector(result);
    cout << endl << endl;
}

int main() {
    // Example 1
    runTest({2, 7, 11, 15}, 9);

    // Example 2
    runTest({3, 2, 4}, 6);

    // Example 3
    runTest({3, 3}, 6);

    return 0;
}
