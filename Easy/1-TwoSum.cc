
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

//Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//You may assume that each input would have exactly one solution, and you may not use the same element twice.
//You can return the answer in any order. 

// More details: https://leetcode.com/problems/two-sum/description/



/*
    Solution:

    Time complexity: O(n).
    We traverse the list containing n elements only once. Each lookup in the table costs only O(1) time.

    Space complexity: O(n).
    The extra space required depends on the number of items stored in the hash table, which stores at most nnn elements.
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        // Loop through each number in the vector.
        for (int i = 0; i < nums.size(); i++) {
            // Calculate the complement of the current number.
            // If nums[i] is a part of the solution, the other part is target - nums[i].
            int complement = target - nums[i]; 
            if (hash.find(complement) != hash.end()) {
                // Return the indices of the two numbers that add up to the target.
                // hash[complement] is the index of the complement,
                // and i is the current index.
                return {hash[complement], i};
            }
            // If the complement is not found, store the current number and its index in the map.
            // This is for future reference when we encounter the complement.
            hash[nums[i]] = i;
        }
        // If no solution is found, return an empty vector. This should never happen.
        return {};
    }
};


/*
    Submission   98.46% faster than other C++ submissions (27/06/2024):


class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i]; 
            if (hash.find(complement) != hash.end()) 
                return {hash[complement], i};
            hash[nums[i]] = i;
        }
        return {};
    }
};


*/


//Test
int main() {
    Solution solution;
    vector<int> nums = {2, 7, 11, 15}; // 2 + 7 = 9 => Indices: 0 and 1
    int target = 9;
    vector<int> result = solution.twoSum(nums, target);
    if (!result.empty()) {
        cout << "Indices: " << result[0] << " and " << result[1] << endl;
    } else {
        cout << "No two sum solution found." << endl;
    }
    return 0;
}

