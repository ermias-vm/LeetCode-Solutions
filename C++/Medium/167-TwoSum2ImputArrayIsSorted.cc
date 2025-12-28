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
            if (sum == target)
                return {++left, ++right};
            else if (sum < target)
                left++;
            else
                right--;
        }
        return {};
    }
};

// Test
int main() {
    Solution solution;
    vector<int> numbers1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = solution.twoSum(numbers1, target1);
    cout << "Test case 1: [" << result1[0] << ", " << result1[1] << "]" << endl;  // [1, 2]

    vector<int> numbers2 = {2, 3, 4};
    int target2 = 6;
    vector<int> result2 = solution.twoSum(numbers2, target2);
    cout << "Test case 2: [" << result2[0] << ", " << result2[1] << "]" << endl;  // [1, 3]

    vector<int> numbers3 = {-1, 0};
    int target3 = -1;
    vector<int> result3 = solution.twoSum(numbers3, target3);
    cout << "Test case 3: [" << result3[0] << ", " << result3[1] << "]" << endl;  // [1, 2]

    return 0;
}
