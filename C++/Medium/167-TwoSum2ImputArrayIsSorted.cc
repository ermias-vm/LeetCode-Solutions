// Description: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

/*
    Approach: Two Pointers

    Use two pointers starting from both ends of the sorted array.
    Calculate sum of elements at both pointers.
    If sum equals target, return 1-indexed positions.
    If sum is too small, move left pointer right to increase sum.
    If sum is too large, move right pointer left to decrease sum.
    Sorted property guarantees exactly one solution exists.

    Time complexity: O(n) - Single pass through the array.
    Space complexity: O(1) - Only pointer variables used.
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() - 1;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) return {++left, ++right};
            else if (sum < target) left++;
            else right--;
        }
        return {};
    }
};

// Test
int main() {
    Solution solution;

    // Example 1: numbers = [2,7,11,15], target = 9
    vector<int> numbers1 = {2, 7, 11, 15};
    vector<int> result1 = solution.twoSum(numbers1, 9);
    cout << "Output: [" << result1[0] << ", " << result1[1] << "]" << endl;

    // Example 2: numbers = [2,3,4], target = 6
    vector<int> numbers2 = {2, 3, 4};
    vector<int> result2 = solution.twoSum(numbers2, 6);
    cout << "Output: [" << result2[0] << ", " << result2[1] << "]" << endl;

    // Example 3: numbers = [-1,0], target = -1
    vector<int> numbers3 = {-1, 0};
    vector<int> result3 = solution.twoSum(numbers3, -1);
    cout << "Output: [" << result3[0] << ", " << result3[1] << "]" << endl;

    return 0;
}
