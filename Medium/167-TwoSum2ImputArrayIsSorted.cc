#include <iostream>
#include <vector>

using namespace std;

// Description:  https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/

//  Approach: Two Pointers

/* 
    Time complexity: O(n), where n is the length of the array.
    Space complexity: O(1), as we are using only constant extra space.

    This approach uses two pointers to find the two numbers that add up to the target.
    - Initialize two pointers, one at the beginning (left) and one at the end (right) of the array.
    - Calculate the sum of the numbers at these two pointers.
    - If the sum is equal to the target, return the indices (1-based).
    - If the sum is less than the target, move the left pointer to the right to increase the sum.
    - If the sum is greater than the target, move the right pointer to the left to decrease the sum.
    - Repeat the process until the two pointers meet.
*/

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0, right = numbers.size() -1;
        while (left < right) {
            int sum  = numbers[left] + numbers[right];
            if (sum == target) return {++left, ++right};
            else if (sum < target) left ++;
            else right--;
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
    cout << "Test case 1: [" << result1[0] << ", " << result1[1] << "]" << endl; // [1, 2]

    vector<int> numbers2 = {2, 3, 4};
    int target2 = 6;
    vector<int> result2 = solution.twoSum(numbers2, target2);
    cout << "Test case 2: [" << result2[0] << ", " << result2[1] << "]" << endl; // [1, 3]

    vector<int> numbers3 = {-1, 0};
    int target3 = -1;
    vector<int> result3 = solution.twoSum(numbers3, target3);
    cout << "Test case 3: [" << result3[0] << ", " << result3[1] << "]" << endl; // [1, 2]

    return 0;
}